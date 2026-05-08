#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
#include "controllers/GameController.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(GameScene);
    ~GameScene();
private:
    GameController* _ctrl;
    void onUndoBtnClick(Ref*);

};

#endif