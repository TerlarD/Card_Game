#pragma once
#ifndef PLAY_FIELD_VIEW_H
#define PLAY_FIELD_VIEW_H

#include "cocos2d.h"
#include "CardView.h"

USING_NS_CC;

class PlayFieldView : public Node
{
public:
    CREATE_FUNC(PlayFieldView);
    bool init() override;

    void addCard(CardView* card);
    void setCardClickCallback(CardClickCallback cb);

private:
    CardClickCallback _cardClickCb;
    std::vector<CardView*> _cardList;
};

#endif