#pragma once
#ifndef STACK_CONTROLLER_H
#define STACK_CONTROLLER_H

#include "models/GameModel.h"
#include "models/UndoModel.h"
#include "managers/UndoManager.h"
#include "views/CardView.h"
#include "views/StackView.h"

class StackController
{
public:
    /**
     * @brief 初始化控制器
     * @param model 游戏数据模型
     * @param undo 撤销管理器
     * @param view 底牌视图
     */
    void init(GameModel* model, UndoManager* undo, StackView* view);
    /**
     * @brief 显示顶部卡牌
     */
    void showTopCard();
    /**
     * @brief 刷新顶部卡牌
     */
    void refreshTopCard();
    /**
     * @brief 更新顶部卡牌（用于匹配成功时）
     * @param card 新的顶部卡牌视图
     */
    void updateTopCard(CardView* card, bool setPosition = true);
    /**
     * @brief 获取顶部卡牌位置
     * @return 顶部卡牌的世界坐标
     */
    cocos2d::Vec2 getTopCardPosition() const;

    CardView* getTopCardView() const;
    StackView* getStackView() const { return _stackView; }
    void setTopCardDirect(CardView* card);
private:
    void onStackClicked();
    void onReserveCardClicked(CardView* card);

private:
    GameModel* _gameModel;
    UndoManager* _undoManager;
    StackView* _stackView;

    friend class GameController;
};
#endif