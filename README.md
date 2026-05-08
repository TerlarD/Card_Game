# CardGame - 卡牌匹配游戏

基于 Cocos2d-x 3.17 框架开发的卡牌匹配游戏。玩家通过点击桌面牌与手牌区顶部牌进行匹配（点数差1即可匹配），目标是消除所有桌面牌。

---

## 目录结构

```
CardGame/
├── Classes/                    # 源代码目录
│   ├── controllers/            # 控制器层
│   │   ├── GameController.cpp/h      # 游戏主控制器
│   │   ├── StackController.cpp/h     # 手牌区控制器
│   │   └── PlayFieldController.cpp/h # 桌面牌区控制器
│   ├── models/                 # 模型层
│   │   ├── CardModel.h               # 卡牌数据模型
│   │   ├── GameModel.h               # 游戏状态模型
│   │   └── UndoModel.h               # 撤销记录模型
│   ├── views/                  # 视图层
│   │   ├── CardView.cpp/h            # 卡牌视图
│   │   ├── StackView.cpp/h           # 手牌区视图
│   │   └── PlayFieldView.cpp/h       # 桌面牌区视图
│   ├── services/               # 服务层
│   │   ├── CardRuleService.cpp/h     # 卡牌匹配规则
│   │   ├── LevelConfigLoader.cpp/h   # 配置加载器
│   │   └── GameModelGenerator.cpp/h  # 模型生成器
│   ├── managers/               # 管理器
│   │   └── UndoManager.cpp/h         # 撤销管理器
│   └── utils/                  # 工具类
│       └── GameConfig.cpp/h          # 游戏配置
├── Resources/                  # 资源目录
│   └── level1.json             # 关卡配置文件
└── proj.win32/                 # Windows 项目文件
```

---

## 模块功能说明

### 控制器层 (controllers/)

| 类名 | 功能 | 职责 | 使用场景 |
|------|------|------|----------|
| **GameController** | 游戏主控制 | 协调各模块、处理游戏流程、管理回退功能 | 游戏初始化、匹配逻辑、回退操作 |
| **StackController** | 手牌区控制 | 管理备用牌堆和顶部牌、处理备用牌点击 | 备用牌翻牌、顶部牌更新、回退处理 |
| **PlayFieldController** | 桌面牌区控制 | 管理桌面牌、处理桌面牌点击、匹配检测 | 桌面牌创建、点击检测、匹配验证 |

### 模型层 (models/)

| 类名 | 功能 | 职责 | 使用场景 |
|------|------|------|----------|
| **CardModel** | 卡牌数据 | 存储卡牌属性（花色、面值、位置） | 所有卡牌相关操作 |
| **GameModel** | 游戏状态 | 存储游戏全局状态（桌面牌、手牌堆、顶部牌） | 游戏状态管理、数据持久化 |
| **UndoModel** | 撤销记录 | 存储操作记录用于回退 | 回退功能实现 |

### 视图层 (views/)

| 类名 | 功能 | 职责 | 使用场景 |
|------|------|------|----------|
| **CardView** | 卡牌显示 | 渲染卡牌外观、处理触摸事件、播放动画 | 卡牌显示、点击交互、移动动画 |
| **StackView** | 手牌区显示 | 渲染备用牌堆和顶部牌 | 手牌区界面展示 |
| **PlayFieldView** | 桌面牌区显示 | 渲染桌面牌布局 | 桌面牌界面展示 |

### 服务层 (services/)

| 类名 | 功能 | 职责 | 使用场景 |
|------|------|------|----------|
| **CardRuleService** | 匹配规则 | 定义卡牌匹配逻辑（点数差1） | 匹配验证 |
| **LevelConfigLoader** | 配置加载 | 从 JSON 加载关卡配置 | 游戏初始化 |
| **GameModelGenerator** | 模型生成 | 将静态配置转换为运行时模型 | 游戏初始化 |

### 管理器 (managers/)

| 类名 | 功能 | 职责 | 使用场景 |
|------|------|------|----------|
| **UndoManager** | 撤销管理 | 管理撤销记录栈、支持回退操作 | 回退功能 |

### 工具类 (utils/)

| 类名 | 功能 | 职责 | 使用场景 |
|------|------|------|----------|
| **GameConfig** | 游戏配置 | 存储游戏常量（位置、尺寸、动画时长） | 全局配置访问 |

---

## 核心类详细说明

### GameController

**功能**：游戏主控制器，负责协调所有模块。

**核心方法**：

| 方法名 | 功能说明 |
|--------|----------|
| `init()` | 初始化游戏，创建各模块实例 |
| `onCardMatch()` | 处理桌面牌匹配事件 |
| `undoLastAction()` | 执行回退操作 |
| `undoMatch()` | 回退匹配操作 |
| `undoStack()` | 回退备用牌操作 |

### CardModel

**数据结构**：

| 字段 | 类型 | 说明 |
|------|------|------|
| `cardId` | int | 卡牌唯一ID |
| `suit` | CardSuitType | 花色（梅花、方块、红桃、黑桃） |
| `face` | CardFaceType | 面值（A、2-10、J、Q、K） |
| `x, y` | float | 位置坐标 |
| `isOpened` | bool | 是否翻开显示 |
| `isInStack` | bool | 是否在手牌堆中 |

### UndoModel

**数据结构**：

| 字段 | 类型 | 说明 |
|------|------|------|
| `type` | UndoType | 操作类型 |
| `card` | CardModel | 被操作的卡牌 |
| `oldTop` | CardModel | 操作前的顶部牌 |
| `newTop` | CardModel | 操作后的顶部牌 |
| `cardOldX, cardOldY` | float | 卡牌原始位置 |
| `topOldX, topOldY` | float | 顶部牌原始位置 |
| `oldStackCards` | vector | 操作前的备用牌堆状态 |

---

## 游戏玩法

1. **匹配规则**：桌面牌与手牌区顶部牌点数差1即可匹配（无花色要求）
2. **操作方式**：
   - 点击桌面牌：与顶部牌匹配，匹配成功则桌面牌移动到顶部位置
   - 点击备用牌：替换顶部牌（平移动画）
   - 点击回退按钮：撤销上一步操作

---

## 如何添加新卡牌

### 方式一：通过配置文件

编辑 `Resources/level1.json`：

```json
{
    "playFieldCards": [
        {
            "CardId": 100,
            "CardSuit": 1,      // 方块
            "CardFace": 2,      // 3
            "X": 200,
            "Y": 300
        }
    ],
    "stackCards": [
        {
            "CardId": 200,
            "CardSuit": 2,      // 红桃
            "CardFace": 3       // 4
        }
    ],
    "topCard": {
        "CardId": 300,
        "CardSuit": 0,          // 梅花
        "CardFace": 4           // 5
    }
}
```

### 方式二：动态创建

```cpp
// 创建新卡牌模型
CardModel newCard;
newCard.cardId = 999;
newCard.suit = CST_DIAMONDS;   // 方块
newCard.face = CFT_THREE;      // 3
newCard.x = 400;
newCard.y = 350;
newCard.isOpened = true;

// 添加到游戏模型
_gameModel->playFieldCards.push_back(newCard);

// 创建视图并添加到场景
CardView* cardView = CardView::create(newCard);
_playCtrl->_playView->addChild(cardView);
_playCtrl->_cardList.push_back(cardView);
```

---

## 如何添加新类型的回退功能

### 步骤一：定义新操作类型

```cpp
// 在 UndoModel.h 中添加
enum UndoType {
    UNDO_NONE,
    UNDO_MATCH_CARD,    // 桌面牌匹配
    UNDO_STACK_NEXT,    // 备用牌翻牌
    UNDO_CUSTOM_ACTION  // 新类型：自定义操作
};
```

### 步骤二：记录撤销数据

```cpp
void GameController::doCustomAction() {
    UndoModel data;
    data.type = UNDO_CUSTOM_ACTION;
    data.card = currentCard;
    data.oldTop = _gameModel->currentTopCard;
    _undoManager->pushRecord(data);
    
    // 执行自定义操作...
}
```

### 步骤三：实现回退逻辑

```cpp
void GameController::undoCustomAction(UndoModel data) {
    // 恢复状态
    _gameModel->currentTopCard = data.oldTop;
    
    // 播放反向动画
    for (auto card : _playCtrl->_cardList) {
        if (card->getCardId() == data.card.cardId) {
            card->runAction(MoveTo::create(0.3f, Vec2(data.cardOldX, data.cardOldY)));
            break;
        }
    }
    
    // 更新视图
    _stackCtrl->refreshTopCard();
}
```

### 步骤四：添加分支判断

```cpp
void GameController::undoLastAction() {
    if (!_undoManager->hasUndoRecord()) return;
    auto data = _undoManager->popRecord();

    switch (data.type) {
        case UNDO_MATCH_CARD:
            undoMatch(data);
            break;
        case UNDO_STACK_NEXT:
            undoStack(data);
            break;
        case UNDO_CUSTOM_ACTION:
            undoCustomAction(data);
            break;
        default:
            break;
    }
}
```

---

## 架构特点

- **MVC 架构**：职责分离，便于维护和扩展
- **模块化设计**：各模块独立，便于测试和复用
- **可扩展性**：新增功能只需添加新模块，不影响现有代码

---

## 构建与运行

### 环境要求

- Cocos2d-x 3.17
- Visual Studio 2017 或更高版本
- Windows 7 或更高版本

### 构建步骤

1. 打开 `proj.win32/CardGame.sln`
2. 选择 Release 或 Debug 配置
3. 点击生成按钮

### 运行

直接运行生成的可执行文件即可。

---

## 开发说明

### 代码规范

- 使用 CamelCase 命名风格
- 类名首字母大写
- 方法名首字母小写
- 变量名使用下划线分隔

### 提交规范

- feat: 添加新功能
- fix: 修复 bug
- docs: 更新文档
- style: 代码风格调整
- refactor: 重构代码

---

## 许可证

MIT License

---

## 作者
Terlar.D
CardGame Development Team