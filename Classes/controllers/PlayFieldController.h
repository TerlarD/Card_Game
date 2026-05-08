#pragma once
#ifndef PLAY_FIELD_CONTROLLER_H
#define PLAY_FIELD_CONTROLLER_H

#include <vector>
#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "views/CardView.h"
#include "views/PlayFieldView.h"

USING_NS_CC;

// 卡牌点击回调类型
typedef std::function<void(CardView*)> CardMatchCallback;

class PlayFieldController
{
public:
    /**
     * @brief 初始化控制器
     * @param model 游戏数据模型
     * @param undo 撤销管理器
     * @param view 游戏区域视图
     */
    void init(GameModel* model, UndoManager* undo, PlayFieldView* view);
    /**
     * @brief 创建所有卡牌
     */
    void createCards();
    /**
     * @brief 设置卡牌匹配回调
     * @param cb 匹配成功时的回调函数
     */
    void setCardMatchCallback(CardMatchCallback cb);

private:
    /**
     * @brief 设置视图层的点击回调
     */
    void setCardClickCallback();
    /**
     * @brief 处理卡牌点击事件
     * @param card 被点击的卡牌视图
     */
    void onCardClicked(CardView* card);
    /**
     * @brief 检查卡牌是否匹配
     * @param card 待匹配卡牌
     * @param top 底牌
     * @return 是否匹配成功
     */
    bool checkMatch(CardModel card, CardModel top);

private:
    GameModel* _gameModel;
    UndoManager* _undoManager;
    PlayFieldView* _playView;
    std::vector<CardView*> _cardList;
    CardMatchCallback _matchCallback;

    friend class GameController;
};

#endif