#include "PlayFieldController.h"
#include "services/CardRuleService.h"

void PlayFieldController::init(GameModel* model, UndoManager* undo, PlayFieldView* view)
{
    _gameModel = model;
    _undoManager = undo;
    _playView = view;
}

void PlayFieldController::createCards()
{
    for (auto& m : _gameModel->playFieldCards)
    {
        auto card = CardView::create(m);
        _playView->addCard(card);
        _cardList.push_back(card);
    }
    setCardClickCallback();
}

void PlayFieldController::setCardMatchCallback(CardMatchCallback cb)
{
    _matchCallback = cb;
}

void PlayFieldController::setCardClickCallback()
{
    _playView->setCardClickCallback([this](CardView* card) {
        this->onCardClicked(card);
        });
}

bool PlayFieldController::checkMatch(CardModel card, CardModel top)
{
    return CardRuleService::canCardMatch(card, top);
}

void PlayFieldController::onCardClicked(CardView* card)
{
    // 检查卡牌是否可以匹配
    if (checkMatch(card->getModel(), _gameModel->currentTopCard))
    {
        // 匹配成功，通知上层控制器
        if (_matchCallback)
        {
            _matchCallback(card);
        }
    }
}