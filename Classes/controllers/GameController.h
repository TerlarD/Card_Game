#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "cocos2d.h"
#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "PlayFieldController.h"
#include "StackController.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"

USING_NS_CC;

class GameController
{
public:
    GameController();
    ~GameController();

    void initGame(Node* root);
    void undoLastAction();

private:
    void onCardMatch(CardView* card);
    void onStackClick();
    void doMatchAnimation(CardView* card);
    void undoMatch(UndoModel data);
    void undoStack(UndoModel data);

private:
    GameModel* _gameModel;
    UndoManager* _undoManager;

    PlayFieldView* _playView;
    StackView* _stackView;
    PlayFieldController* _playCtrl;
    StackController* _stackCtrl;
};

#endif