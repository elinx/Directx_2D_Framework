//Date: 2013-10-28 16:42
//Modify:修改Sprite的显示范围，现在Sprite不能显示超过屏幕区；
//		 修改窗口的高度，又原来的高度增加了24，这样整个客户区的高度就是600了

//Date: 2013-10-31 23:01
//Modify:背景用了一个OffsetPlainBuffer这样就不会掉帧了，终于解决了掉帧了
//		更改了鼠标的形状，发现了不合理的地方，graphics device应该是全局的或者
//		把整个winmain函数都包装成一个类

//Date: 2013-11-4  19:40
//Modify:把数据从Graphic分离出来，增加一个智能体的类，这个类负责AI的逻辑和数据的管理，
//		这样就不用使的Game类显得很乱。

//Date: 2013-11-5 18:11
//Modify:实现了小规模的状态自动机，增加了两个状态，这两个状态同时对应于不同的控制策略
//      代码需要优化，因为有的地方使用了权宜之计，主要问题有：1、agent父类的使用问题
//		2、枚举返回值类型出错，不能编译问题；3、函数对象的使用问题，这里的方法貌似是对的
//		但是感觉很啰嗦，干嘛不直接使用函数指针呢？(当然这里的控制策略都是member function,不能用函数指针的)

//Date: 2013-11-13 15:23(从另外一个单独的工程合并而来，用来实现TileMap)
// Four Step:
// 1: Parser the map, read the tile and layer information(DONE!)
// 2: Load sprites need by map(How to load and how to store the texture)
// 3: Rearrange the map information and make a clean surface in the end.
// 4: Swap the surface created to the main surface
// Appendix: make a camera!

// Two way to store the tileset image
// 1: Store in a texture vector
// 2: Store in a plain surface(Try this first!)

//Date: 2013-11-22 17:07要改变一些坐标
//因为之前agent的坐标用的都是相对坐标(即相对于窗口的坐标)，当在地图上显示的时候就会not easy，目前的
//想法就是把所有的坐标都转为相对于地图的坐标(暂且称为绝对坐标)。