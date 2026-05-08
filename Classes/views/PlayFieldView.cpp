#include "PlayFieldView.h"
#include "configs/models/GameConfig.h"
#include "configs/models/CardResConfig.h"

bool PlayFieldView::init()
{
    if (!Node::init()) return false;

    static GameConfig cfg;
    setContentSize(Size(cfg.designWidth, cfg.playFieldHeight));
    return true;
}

void PlayFieldView::addCard(CardView* card)
{
    addChild(card);
    _cardList.push_back(card);
    // 如果回调已经设置，立即应用
    if (_cardClickCb) {
        card->setClickCallback(_cardClickCb);
    }
}

void PlayFieldView::setCardClickCallback(CardClickCallback cb)
{
    _cardClickCb = cb;
    // 更新所有已存在卡牌的回调
    for (auto card : _cardList) {
        card->setClickCallback(cb);
    }
}