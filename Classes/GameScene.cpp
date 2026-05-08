#include "GameScene.h"
#include "configs/models/GameConfig.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
        return false;

    GameConfig cfg;
    LayerColor* bg = LayerColor::create(Color4B(20, 20, 20, 255),
        cfg.designWidth, cfg.designHeight);
    this->addChild(bg, -1);

    _ctrl = new GameController();
    _ctrl->initGame(this);

    // 按钮全部走配置
    MenuItemLabel* undoBtn = MenuItemLabel::create(
        Label::createWithTTF(cfg.undoBtnText, cfg.fontName, cfg.btnFontSize),
        CC_CALLBACK_1(GameScene::onUndoBtnClick, this)
    );
    Menu* menu = Menu::create(undoBtn, nullptr);
    menu->setPosition(900, 120);
    this->addChild(menu, 999);

    return true;
}

void GameScene::onUndoBtnClick(Ref* sender)
{
    if (_ctrl) {
        _ctrl->undoLastAction();
    }
}

GameScene::~GameScene()
{
    CC_SAFE_DELETE(_ctrl);
}