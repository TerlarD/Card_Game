#include "GameController.h"
#include "services/JsonParseService.h"
#include "services/CardRuleService.h"
#include "services/GameModelGenerator.h"
#include "models/UndoModel.h"
#include "configs/loaders/LevelConfigLoader.h"

GameController::GameController()
{
    _gameModel = new GameModel();
    _undoManager = new UndoManager();

    _playView = PlayFieldView::create();
    _stackView = StackView::create();

    _playCtrl = new PlayFieldController();
    _stackCtrl = new StackController();
}

GameController::~GameController()
{
    CC_SAFE_DELETE(_gameModel);
    CC_SAFE_DELETE(_undoManager);
    CC_SAFE_DELETE(_playCtrl);
    CC_SAFE_DELETE(_stackCtrl);
}

void GameController::initGame(Node* root)
{
    // 1. 加载静态配置（CONFIGS层）
    LevelConfig config = LevelConfigLoader::loadLevel("level1.json");

    // 2. 通过服务层转换为运行时数据（SERVICES层）
    *_gameModel = GameModelGenerator::generateFromConfig(config);

    root->addChild(_playView);
    root->addChild(_stackView);

    _playCtrl->init(_gameModel, _undoManager, _playView);
    _stackCtrl->init(_gameModel, _undoManager, _stackView);

    _playCtrl->createCards();
    _stackCtrl->showTopCard();

    _playCtrl->setCardMatchCallback([this](CardView* c) { this->onCardMatch(c); });
    _stackView->setStackClickCallback([this]() { this->onStackClick(); });
}

void GameController::onCardMatch(CardView* card)
{
    auto cardModel = card->getModel();
    auto topModel = _gameModel->currentTopCard;

    // 记录撤销数据
    UndoModel data;
    data.type = UNDO_MATCH_CARD;
    data.card = cardModel;
    data.oldTop = topModel;
    data.cardOldX = card->getPositionX();
    data.cardOldY = card->getPositionY();
    _undoManager->pushRecord(data);

    // 执行匹配动画
    doMatchAnimation(card);
}

void GameController::doMatchAnimation(CardView* card)
{
    // 获取目标位置（顶部牌位置）
    Vec2 targetPos = _stackCtrl->getTopCardPosition();

    // 保存当前位置作为起点
    Vec2 startPos = card->getPosition();

    // 防止自动释放
    card->retain();

    // 从主牌区移除卡牌（保留对象）
    card->removeFromParentAndCleanup(false);

    // 添加到备用牌区作为新的顶部牌（不设置位置）
    _stackCtrl->updateTopCard(card, false);

    // 设置起始位置为原来的位置
    card->setPosition(startPos);

    // 播放移动动画
    card->runAction(Sequence::create(
        MoveTo::create(0.3f, targetPos),
        CallFunc::create([card]() { card->release(); }),
        nullptr));

    // 更新模型
    _gameModel->currentTopCard = card->getModel();
}

void GameController::onStackClick()
{
    if (_gameModel->stackCards.size() <= 1) return;

    UndoModel data;
    data.type = UNDO_STACK_NEXT;
    data.oldTop = _gameModel->currentTopCard;
    _undoManager->pushRecord(data);

    _gameModel->stackCards.pop_back();
    _gameModel->currentTopCard = _gameModel->stackCards.back();
    _stackCtrl->refreshTopCard();
}


CardView* StackController::getTopCardView() const
{
    return _stackView->getTopCard();
}

void StackController::setTopCardDirect(CardView* card)
{
    _stackView->setTopCardDirect(card);
}

void GameController::undoLastAction()
{
    if (!_undoManager->hasUndoRecord()) return;
    auto data = _undoManager->popRecord();

    if (data.type == UNDO_MATCH_CARD)
        undoMatch(data);
    else
        undoStack(data);
}

//桌面牌回退
void GameController::undoMatch(UndoModel data)
{
    // 创建一个新的卡牌视图来播放回退动画
    CardView* backCard = CardView::create(data.card);
    backCard->setOpenState(true);

    // 获取顶部位置作为起始位置
    Vec2 topPos = _stackCtrl->getTopCardPosition();
    backCard->setPosition(topPos);

    // 添加到游戏区域
    _playCtrl->_playView->addChild(backCard, 10);
    _playCtrl->_cardList.push_back(backCard);

    // 播放反向动画
    backCard->runAction(MoveTo::create(0.3f, Vec2(data.cardOldX, data.cardOldY)));

    // 恢复顶部牌
    _gameModel->currentTopCard = data.oldTop;
    _stackCtrl->refreshTopCard();
}

//备用牌回退
void GameController::undoStack(UndoModel data)
{
    // 创建一个新的卡牌视图来播放回退动画
    CardView* backCard = CardView::create(data.newTop);
    backCard->setOpenState(true);

    // 获取顶部位置作为起始位置
    Vec2 topPos = _stackCtrl->getTopCardPosition();
    backCard->setPosition(topPos);

    // 添加到备用牌区
    _stackCtrl->getStackView()->addChild(backCard, 1);

    // 播放反向动画
    backCard->runAction(MoveTo::create(0.3f, Vec2(data.cardOldX, data.cardOldY)));

    // 更新模型和视图
    _gameModel->currentTopCard = data.oldTop;
    _gameModel->stackCards = data.oldStackCards;
    _stackCtrl->getStackView()->updateReserveCards(_gameModel->stackCards);
    _stackCtrl->refreshTopCard();
}
