# SlopeCraftGlassBuilder
用于为立体地图画“搭桥”的库，可以让立体地图画更容易建造

A bridge-builder lib for SlopeCraft, making 3d map arts easier to be built

“搭桥”是一种可以方便立体地图画的建造的新技术。立体地图画的每个水平切片都是很多分散的方块，无损压缩之后甚至在z方向上也不再连续；加之常规的建筑方式都是沿y轴一层层向上建造，立体地图画建造难度极高。因此我想在每隔几层就用玻璃块将这些高度分散的方块连接起来，把它们加入到投影中，方便建造。这需要使用尽可能少的玻璃将所有方块都连接起来，这一过程称为“搭桥”。

玻璃桥的搭建方式有几种方案：TSP方案和最小生成树方案。TSP方案由TSP问题得到灵感，让玩家可以一笔画走遍投影y切片中的每一个方块。最小生成树方案则源于图论中的最小生成树问题，先将y切片的每个方块都当做一个顶点，连接所有顶点形成一个完全图（无向图），每条边的权值就是它的长度。在这个庞大的完全图中构建最小生成树，就可以将所有方块连接起来。


我曾经使用过遗传算法，但效果很不好，性能也极差，迭代出来的结果总是很不可名状。在tsp问题和最小生成树方案上摇摆了一段时间后，最后选择了Prim算法。事实说明……AI可能是万能的，但不总是最好的。该用传统算法的地方就尽量不能用ai。

I've tried genetic algorithm, but the result was far from satisfying and the time cosuming was unbearable. Actually the results are usually unnameable. After wagging between TSP plan and minium spawing tree plan, I chose the minium spawing tree plan, which corresponds to Prim algorithm. It gave me a class that AI is powerful but not always the best choice, when 'common' algorithm provides a bearable choice, just choose it.

