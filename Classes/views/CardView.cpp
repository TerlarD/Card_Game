#include "CardView.h"
#include "configs/models/GameConfig.h"
#include "configs/models/CardResConfig.h"
#include "utils/StringUtil.h"

CardView* CardView::create(const CardModel& model)
{
    auto ret = new CardView();
    if (ret && ret->init(model)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init(const CardModel& model)
{
    if (!Sprite::init()) return false;

    _model = model;
    _isTouchInside = false;
    _suitSprite = nullptr;
    _numberSprite = nullptr;

    // 加载牌底背景
    static CardResConfig resConfig;
    setTexture(resConfig.cardBack);

    // 初始化花色和数字精灵
    _suitSprite = Sprite::create();
    _numberSprite = Sprite::create();
    addChild(_suitSprite, 1);
    addChild(_numberSprite, 2);

    setPosition(model.x, model.y);
    refreshUI();

    // 触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void CardView::refreshUI()
{
    // 静态配置，统一管理卡牌图片资源
    static CardResConfig resConfig;

    if (!_model.isOpened) {
        setTexture(resConfig.cardBack);
        _suitSprite->setVisible(false);
        _numberSprite->setVisible(false);
        return;
    }

    setTexture(resConfig.cardFrontBase);
    loadSuitSprite();
    loadNumberSprite();

    _suitSprite->setVisible(true);
    _numberSprite->setVisible(true);
}

void CardView::setOpenState(bool open)
{
    _model.isOpened = open;
    refreshUI();
}

void CardView::updateModel(const CardModel& model)
{
    _model = model;
    refreshUI();
}

void CardView::playMoveTo(Vec2 pos, float duration)
{
    // 防御性检查：防止悬空指针访问
    if (!this || this == (CardView*)0xDDDDDDDD || this == (CardView*)0xCCCCCCCC) {
        return;
    }

    // 动画时间也走配置
    static GameConfig gameConfig;
    runAction(MoveTo::create(gameConfig.cardMoveDuration, pos));
}

int CardView::getCardId() const 
{ 
    return _model.cardId; 
}

CardModel CardView::getModel() const 
{ 
    return _model; 
}

void CardView::setClickCallback(CardClickCallback cb)
{
    _clickCallback = cb;
}

bool CardView::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 loc = touch->getLocation();
    _isTouchInside = getBoundingBox().containsPoint(loc);
    return _isTouchInside;
}

void CardView::onTouchEnded(Touch* touch, Event* event)
{
    if (_isTouchInside && _clickCallback) {
        _clickCallback(this);
    }
}

void CardView::loadSuitSprite()
{
    static CardResConfig resConfig;
    std::string path;

    switch (_model.suit) {
    case CST_CLUBS:    path = resConfig.suitClubs; break;
    case CST_DIAMONDS: path = resConfig.suitDiamonds; break;
    case CST_HEARTS:   path = resConfig.suitHearts; break;
    case CST_SPADES:   path = resConfig.suitSpades; break;
    default: break;
    }

    if (!path.empty()) {
        _suitSprite->setTexture(path);
        _suitSprite->setPosition(getContentSize().width * 0.8f, getContentSize().height * 0.8f);
    }
}

void CardView::loadNumberSprite()
{
    std::string path = getNumberImagePath();
    if (!path.empty()) {
        _numberSprite->setTexture(path);
        _numberSprite->setPosition(getContentSize().width / 2, getContentSize().height / 2);
    }
}

std::string CardView::getNumberImagePath()
{
    static CardResConfig resConfig;

    if (_model.suit == CST_HEARTS || _model.suit == CST_DIAMONDS) {
        switch (_model.face) {
        case CFT_ACE:   return resConfig.numberRedA;
        case CFT_TWO:   return resConfig.numberRed2;
        case CFT_THREE: return resConfig.numberRed3;
        case CFT_FOUR:  return resConfig.numberRed4;
        case CFT_FIVE:  return resConfig.numberRed5;
        case CFT_SIX:   return resConfig.numberRed6;
        case CFT_SEVEN: return resConfig.numberRed7;
        case CFT_EIGHT: return resConfig.numberRed8;
        case CFT_NINE:  return resConfig.numberRed9;
        case CFT_TEN:   return resConfig.numberRed10;
        case CFT_JACK:  return resConfig.numberRedJ;
        case CFT_QUEEN: return resConfig.numberRedQ;
        case CFT_KING:  return resConfig.numberRedK;
        default: break;
        }
    }
    else {
        switch (_model.face) {
        case CFT_ACE:   return resConfig.numberBlackA;
        case CFT_TWO:   return resConfig.numberBlack2;
        case CFT_THREE: return resConfig.numberBlack3;
        case CFT_FOUR:  return resConfig.numberBlack4;
        case CFT_FIVE:  return resConfig.numberBlack5;
        case CFT_SIX:   return resConfig.numberBlack6;
        case CFT_SEVEN: return resConfig.numberBlack7;
        case CFT_EIGHT: return resConfig.numberBlack8;
        case CFT_NINE:  return resConfig.numberBlack9;
        case CFT_TEN:   return resConfig.numberBlack10;
        case CFT_JACK:  return resConfig.numberBlackJ;
        case CFT_QUEEN: return resConfig.numberBlackQ;
        case CFT_KING:  return resConfig.numberBlackK;
        default: break;
        }
    }
    return "";
}