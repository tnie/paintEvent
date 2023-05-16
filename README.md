# 场景添加 100万图形项

初始化过程较长，使用过程流畅：缩放或者滑动窗口的滚动条没有明显延迟。

占用很大内存，8G+

# 多模式下事件分发

新建之后，需要交互（被选中、可移动等）的图形项有哪些？新建之后是否只需要显示即可？

- 如果比较多，就需要像目前的电子海图软件那样分多种模式（代码好多条件分支）；
- 如果很少，其实优化调整交互就能使代码简洁很多；（我倾向于如此，进一步确认 @todo）

存在 `class item_baseMap_msg` 事件分发图形项就很扯淡:

- 因为 Z 值最小，所以场景分发事件时优先给到其他图形项
- 此图形项覆盖整个视图，所以“兜底”所有的事件（限于场景分发的）
- 然后将键鼠事件分发给工具类、新建图形项等（主要是选点定位）
- 因为拿不到移动事件（图形项只能拿到鼠标按下时的移动事件），所以还得视图/场景做

为什么不删掉这个分发图形项，使用场景自身的事件分发机制呢？

- 如何判断某个事件已经被场上的图形项消费了（进而不再处理）？比如
新建航线时，已添加的航路点可以移动调整。怎么实现？

我的目标：删掉 `class item_baseMap_msg` 图形项；删掉 `enum SceneMode` 枚举类型（至少是
删除其 90% 的枚举值，只需要保留三两种状态即可）

这个其实是产品交互设计的细节了。

- 不新建图形项时，鼠标点击事件优先用于选中已有的（可选中的）图形项

    - 移动选中的图形项
    - 没有选中的图形项时，移动地图

- 新建图形项（选点定位等操作）时，能否叠加



# todo

2. 图形项可以选中，拖动位置
3. 图形项可以移动（随机移动或统一）
4. 场景的背景可以按下移动（随机换图）
5. 缩放

# QGraphicsView

图形项并非直接在 view 上绘制，view 作为可滑动窗口，包含 viewport 和两个滑动条。

图形项实际是绘制在 viewport 组件上。

键鼠事件是上层的 viewport 触发的，
但在 view-scene 框架中将 viewport 键鼠事件的处理函数映射到了 view 的成员上。
使得用户在大多时候对于 viewport 是无感知的，
但会造成 `setMouseTracking()` 等修改组件属性时用错对象带来反直觉的现象。

> For convenience, `QAbstractScrollArea` makes all viewport events available in the virtual `viewportEvent()` handler.
>
> QWidget's specialized handlers are remapped to viewport events in the cases where this makes sense.
