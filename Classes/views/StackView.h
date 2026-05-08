#pragma once
#ifndef STACK_VIEW_H
#define STACK_VIEW_H

#include "cocos2d.h"
#include "CardView.h"

USING_NS_CC;

typedef std::function<void()> StackClickCallback;

typedef std::function<void(CardView*)> ReserveCardClickCallback;

class StackView : public Node
{
public:
    CREATE_FUNC(StackView);
    bool init() override;

    void setTopCard(CardView* card, bool setPosition = true);
    void setStackClickCallback(StackClickCallback cb);
    void setReserveCardClickCallback(ReserveCardClickCallback cb);
    cocos2d::Vec2 getTopCardPosition() const;
    void updateReserveCards(const std::vector<CardModel>& cards);  // 更新备用牌堆显示
    void addReserveCard(CardView* card);
    void swapToTopCard(CardView* card);
    void swapCards(CardView* newTop, CardView* oldTop);
    void updateReserveCardsData(const std::vector<CardModel>& cards);
    void setTopCardDirect(CardView* card);
    CardView* getTopCard() const { return _topCardView; }

private:
    bool onTouchBegan(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    void onReserveCardClicked(CardView* card);

private:
    CardView* _topCardView;
    std::vector<CardView*> _reserveCardViews;  // 备用牌堆视图列表
    StackClickCallback _clickCb;
    ReserveCardClickCallback _reserveCardClickCb;
    bool _isTouchInside;
};

#endif