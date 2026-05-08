#include "StackController.h"
#include "models/UndoModel.h"
#include "configs/models/GameConfig.h"

void StackController::init(GameModel* model, UndoManager* undo, StackView* view)
{
    _gameModel = model;
    _undoManager = undo;
    _stackView = view;

    _stackView->setStackClickCallback([this]() {
        this->onStackClicked();
        });
    // 设置备用牌点击回调
    _stackView->setReserveCardClickCallback([this](CardView* card) {
        this->onReserveCardClicked(card);
        });
}

void StackController::onReserveCardClicked(CardView* card)
{
    // 获取被点击牌的数据
    CardModel clickedModel = card->getModel();
    Vec2 clickedPos = card->getPosition();

    // 获取顶部牌位置
    static GameConfig cfg;
    Vec2 topPos = Vec2(cfg.stackCardX + 200, cfg.stackCardY);

    // 获取旧顶部牌
    CardModel oldTopModel = _gameModel->currentTopCard;

    // 记录撤销数据（包含完整状态）
    UndoModel undoRec;
    undoRec.type = UNDO_STACK_NEXT;
    undoRec.card = clickedModel;
    undoRec.oldTop = oldTopModel;
    undoRec.newTop = clickedModel;
    undoRec.cardOldX = clickedPos.x;
    undoRec.cardOldY = clickedPos.y;
    undoRec.topOldX = topPos.x;
    undoRec.topOldY = topPos.y;
    undoRec.oldStackCards = _gameModel->stackCards;  // 保存操作前的备用牌堆状态
    _undoManager->pushRecord(undoRec);

    // 1. 更新模型
    _gameModel->currentTopCard = clickedModel;

    // 在备用牌堆中找到被点击的牌并替换为旧顶部牌
    auto& cards = _gameModel->stackCards;
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (it->cardId == clickedModel.cardId) {
            *it = oldTopModel;
            break;
        }
    }

    // 2. 创建新的顶部牌视图
    CardView* newTopCard = CardView::create(clickedModel);
    newTopCard->setOpenState(true);
    newTopCard->setPosition(clickedPos);  // 起始位置是被点击牌的位置
    newTopCard->retain();

    // 3. 设置为顶部牌
    _stackView->setTopCard(newTopCard, false);

    // 4. 播放平移动画
    newTopCard->runAction(MoveTo::create(0.3f, topPos));
    newTopCard->release();

    // 5. 更新备用牌视图
    _stackView->updateReserveCards(cards);
}

void StackController::showTopCard()
{
    if (_gameModel->stackCards.empty())
        return;

    _gameModel->currentTopCard = _gameModel->stackCards.back();
    refreshTopCard();
    // 更新备用牌堆显示
    _stackView->updateReserveCards(_gameModel->stackCards);
}

void StackController::refreshTopCard()
{
 //   static GameConfig cfg;
    CardView* newCard = CardView::create(_gameModel->currentTopCard);
//    _stackView->setTopCard(newCard, false);  // false = 不立即设置位置
    _stackView->setTopCard(newCard);

    // MoveTo平移动画：从左侧平移到顶部牌位置
//    newCard->runAction(MoveTo::create(0.3f, Vec2(cfg.stackCardX, cfg.stackCardY)));
}

void StackController::updateTopCard(CardView* card, bool setPosition)
{
    _stackView->setTopCard(card, setPosition);
}

cocos2d::Vec2 StackController::getTopCardPosition() const
{
    return _stackView->getTopCardPosition();
}

void StackController::onStackClicked()
{
/*    if (_gameModel->stackCards.size() <= 1)
        return;

    UndoModel undoRec;
    undoRec.type = UNDO_STACK_NEXT;
    undoRec.oldTop = _gameModel->currentTopCard;
    _undoManager->pushRecord(undoRec);

    _gameModel->stackCards.pop_back();
    _gameModel->currentTopCard = _gameModel->stackCards.back();

    // 创建新卡牌并播放平移动画（从左侧备用牌堆位置平移到右侧顶部）
    CardView* newCard = CardView::create(_gameModel->currentTopCard);
    static GameConfig cfg;
    // 设置起始位置（左侧备用牌堆位置）
    newCard->setPosition(cfg.stackCardX - 150, cfg.stackCardY);

    _stackView->setTopCard(newCard, false);  // false = 不立即设置位置

    // MoveTo平移动画：从左侧平移到右侧顶部牌位置
    newCard->runAction(MoveTo::create(0.3f, Vec2(cfg.stackCardX, cfg.stackCardY)));

    // 更新备用牌堆显示
    _stackView->updateReserveCards(_gameModel->stackCards);
*/

// 点击手牌区空白区域不处理
// 备用牌的点击由 onReserveCardClicked() 处理
}