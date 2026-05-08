#include "StackView.h"
#include "configs/models/GameConfig.h"
#include "configs/models/CardResConfig.h"

bool StackView::init()
{
    if (!Node::init()) return false;

    static GameConfig cfg;
    setContentSize(Size(cfg.designWidth, cfg.stackHeight));
    setPosition(0, 0);
    _isTouchInside = false;

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(StackView::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(StackView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void StackView::updateReserveCards(const std::vector<CardModel>& cards)
{
    // 移除旧的备用牌视图
    for (auto cardView : _reserveCardViews) {
        // 检查指针是否有效
        if (cardView &&
            cardView != reinterpret_cast<CardView*>(0xDDDDDDDD) &&
            cardView != reinterpret_cast<CardView*>(0xCCCCCCCC)) {
            cardView->removeFromParent();
        }
    }
    _reserveCardViews.clear();

    // 创建新的备用牌视图（正面朝上，从右到左排列）
    static GameConfig cfg;
    float startX = cfg.stackCardX - 300;  // 起始位置（左侧）
    float y = cfg.stackCardY;
    float spacing = 80;

    for (size_t i = 0; i < cards.size() && i < 5; ++i) {  // 最多显示5张
        CardView* cardView = CardView::create(cards[i]);
        cardView->setPosition(startX + i * spacing, y);  // 依次向右偏移
        cardView->setOpenState(true);  // 正面朝上
        addChild(cardView, 1);
        _reserveCardViews.push_back(cardView);

        // 设置备用牌点击回调
        cardView->setClickCallback([this](CardView* card) {
            this->onReserveCardClicked(card);
        });
    }
}

void StackView::onReserveCardClicked(CardView* card)
{
    if (_reserveCardClickCb) {
        _reserveCardClickCb(card);
    }
}

void StackView::setReserveCardClickCallback(ReserveCardClickCallback cb)
{
    _reserveCardClickCb = cb;
}

void StackView::addReserveCard(CardView* card)
{
    if (!card) return;
    card->retain();  // 增加引用计数防止释放
    addChild(card, 1);
    _reserveCardViews.push_back(card);
    card->release();
}

void StackView::swapToTopCard(CardView* card)
{
    if (!card) return;

    // 从备用牌列表中移除
    auto it = std::find(_reserveCardViews.begin(), _reserveCardViews.end(), card);
    if (it != _reserveCardViews.end()) {
        _reserveCardViews.erase(it);
    }

    // 移除旧的顶部牌
    if (_topCardView && _topCardView->getParent()) {
        _topCardView->removeFromParent();
    }

    // 设置新的顶部牌
    _topCardView = card;
    // 检查是否已经是子节点
    if (card->getParent() == this) {
        // 已经是子节点，只需更新层级
        card->setLocalZOrder(2);
    }
    else {
        // 不是子节点，需要添加
        if (card->getParent()) {
            card->removeFromParent();
        }
        addChild(card, 2);
    }
}

void StackView::swapCards(CardView* newTop, CardView* oldTop)
{
    // 不修改 _reserveCardViews 的顺序
    // 只更新层级和设置新顶部牌
    if (oldTop) {
        oldTop->setLocalZOrder(1);  // 设置为备用牌层级
    }

    // 设置新顶部牌
    _topCardView = newTop;
    newTop->setLocalZOrder(2);  // 设置为顶部牌层级
}

void StackView::setTopCardDirect(CardView* card)
{
    // 移除旧的顶部牌
    if (_topCardView && _topCardView->getParent()) {
        _topCardView->removeFromParent();
    }
    _topCardView = card;
}

void StackView::updateReserveCardsData(const std::vector<CardModel>& cards)
{
    // 确保数据和视图数量匹配
    if (_reserveCardViews.size() != cards.size()) {
        // 如果不匹配，重新创建所有视图
        updateReserveCards(cards);
        return;
    }

    // 更新备用牌数据
    for (size_t i = 0; i < _reserveCardViews.size(); ++i) {
        CardView* cardView = _reserveCardViews[i];
        // 防御性检查：确保指针有效
        if (!cardView ||
            cardView == reinterpret_cast<CardView*>(0xDDDDDDDD) ||
            cardView == reinterpret_cast<CardView*>(0xCCCCCCCC)) {
            continue;
        }
        cardView->updateModel(cards[i]);
    }
}

void StackView::setTopCard(CardView* card, bool setPosition)
{
    // 定义无效指针检查函数
    auto isValidPtr = [](CardView* ptr) {
        if (!ptr) return false;
        if (ptr == reinterpret_cast<CardView*>(0xDDDDDDDD)) return false;
        if (ptr == reinterpret_cast<CardView*>(0xCCCCCCCC)) return false;
        if (ptr == reinterpret_cast<CardView*>(0xFAFAFAFA)) return false;
        if (ptr == reinterpret_cast<CardView*>(0xDEADDEAD)) return false;
        return true;
        };

    // 防御性检查：检测无效指针
    if (!isValidPtr(card)) {
        CCLOG("StackView::setTopCard - Invalid card pointer detected!");
        return;
    }

    // 如果是同一张卡，不需要重复设置
    if (_topCardView == card) {
        return;
    }

    // 移除旧牌
    if (isValidPtr(_topCardView) && _topCardView->getParent()) {
        _topCardView->removeFromParentAndCleanup(true);
    }
    _topCardView = nullptr;

    // 设置新牌
    _topCardView = card;
    if (isValidPtr(card)) {
        // 从备用牌列表中移除（如果存在）
        auto it = std::find(_reserveCardViews.begin(), _reserveCardViews.end(), card);
        if (it != _reserveCardViews.end()) {
            _reserveCardViews.erase(it);
        }

        // 检查是否已经是当前节点的子节点
        // 确保卡牌没有父节点
        Node* parent = card->getParent();
        if (parent == this) {
            // 已经是子节点，只需更新层级
            card->setLocalZOrder(2);
        }
        else {
            // 从其他父节点移除并添加
            if (parent) {
                card->removeFromParent();
            }
            addChild(card, 2);  // 层级高于备用牌
        }
        // 根据参数决定是否设置位置：false时保持当前位置，用于动画
        if (setPosition) {
            static GameConfig cfg;
            card->setPosition(cfg.stackCardX + 200, cfg.stackCardY);  // 右移顶部牌位置
        }
    }

}

cocos2d::Vec2 StackView::getTopCardPosition() const
{
    if (_topCardView) {
        return _topCardView->getPosition();
    }
    static GameConfig cfg;
    return Vec2(cfg.stackCardX, cfg.stackCardY);
}

void StackView::setStackClickCallback(StackClickCallback cb)
{
    _clickCb = cb;
}

bool StackView::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 loc = touch->getLocation();
    _isTouchInside = getBoundingBox().containsPoint(loc);
    return _isTouchInside;
}

void StackView::onTouchEnded(Touch*, Event*)
{
    if (_isTouchInside && _clickCb) {
        _clickCb();
    }
}