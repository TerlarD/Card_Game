#pragma once
#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include "cocos2d.h"
#include "models/CardModel.h"

USING_NS_CC;

class CardView;

// 点击回调
typedef std::function<void(CardView*)> CardClickCallback;

class CardView : public Sprite
{
public:
    static CardView* create(const CardModel& model);
    bool init(const CardModel& model);

    void setClickCallback(CardClickCallback cb);
    void refreshUI();           // 刷新图片
    void setOpenState(bool open); // 设置翻开/覆盖
    void playMoveTo(Vec2 pos, float duration = 0.25f); // 移动动画
    void updateModel(const CardModel& model);  // 更新模型数据

    int getCardId() const;
    CardModel getModel() const;

private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    void loadSuitSprite();
    void loadNumberSprite();
    std::string getNumberImagePath();

private:
    CardModel _model;
    CardClickCallback _clickCallback;
    bool _isTouchInside;

    Sprite* _suitSprite;
    Sprite* _numberSprite;
};

#endif