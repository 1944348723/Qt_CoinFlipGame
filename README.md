# Qt_CoinFlipGame

该项目是我在B站看完Qt教程后跟着做的，有两个版本。
FlipCoin是我大致跟着视频敲的，有的地方跟视频有出入。
MyFlipCoin是跟着视频敲完后，我自己又独立的敲了一遍，并对原来的代码进行了重构、封装。

## 项目中需要注意的点
### 1. Qt中文乱码问题
  我没有太深入的去学习底层的，从网上的一些博客上了解了后，大致是源码字符集和执行字符集不统一就可能导致乱码，这里的乱码指的是程序跑起来之后的显示乱码，不是文本文件打开乱码。
  想深入了解可以看看我在网上找到的感觉写的比较好的博客：https://jiangxueqiao.com/post/1376508302.html。

  如果安装Qt时选了mingw，那么大概率没有中文乱码问题，因为Qt编辑器默认源码字符集为utf-8，而mingw编译器的默认执行字符集也为utf-8。

  如果用的是msvc编译器，很可能跟我之前一样被折磨过。
  有很多在写代码时进行修改的方法，像什么在字符串常量前加"u8"，或者什么toLatin1、toLocal8bit，很麻烦，而且可能不知道原理。
  
  其实也就是因为在中文系统下，msvc编译器默认使用GB2312作为执行字符集。那么只要让源码字符集和执行字符集统一就行了。
  一是在Qt中修改编辑器设置，即源码字符集，将编码改为GB2312。二是在.pro文件中添加编译选项：msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8，将执行字符集改为utf-8，
  这段代码在我的.pro文件中有，但是被注释掉了，因为是针对msvc编译器的。我推荐使用第二种方案，因为utf-8是国际化的编码，通用性较强，很多编辑器都默认使用utf-8。
### 2. 场景切换时的闪烁问题
  这个游戏有三种场景，分别是点开游戏后的默认场景MainScene、选择关卡场景LevelSelectionScene和游玩场景PlayScene。
  
  视频中老师的设计是，三种场景都继承自QMainWindow，每个场景都从头开始写，切换场景就是隐藏(或删除)上一个场景，然后显示下一个场景。
  由于每个场景是个独立的QMainWindow，所以在切换时窗口会有闪烁，甚至加载的慢的话会清楚的看到先关闭了原来的窗口，然后创建了一个新的窗口

  为了避免上述现象，我在设计上进行了修改。首先，由于三种场景的窗口大小、图标和菜单栏都是相同的，所以我写了一个BaseWindow，先将这些都设置好。
  然后，三种场景我也都分别写一个类，这样管理起来很清晰，但不同的是我让它们继承自QWidget。
  我的思路是，QMainWindow不是有个certralWidget，场景切换时只要将上一个场景从baseWindow中取下来(`takeCentralWidget()`)，然后将下一个场景设置成centralWindow就行了。
  这样就避免了切换时场景时的闪烁问题
### 3. 游戏场景的创建
  游戏场景中有左下角关卡显示、右下角返回按钮、放硬币的格子、硬币、胜利后的图标、还有背景音乐等音效。
  不同关卡间改变的只有左下角的关卡数和硬币的初始布局。
  
  视频中的方法是每次进入关卡时实时创建关卡，离开时就将关卡删了，这样做确实比较节约内存，不用的空间很快就释放了，但每次进入关卡时要重新加载很多东西。

  我的方法则是，提前将游玩场景通用的部分创建好，每次进入关卡只需设置下左下角的文本，创建硬币和进行一些小的初始化操作就行了，离开时只将硬币删除（甚至可以改成不删除）。
  这样做的好处是进入游戏场景比较快，不过这个游戏太小了，估计看不出区别。
  坏处是即使在主场景或关卡选择场景中，游玩场景也会一直占用内存。但其实对于游戏来说，本来大多数时间就是在游玩场景中，所以这个问题应该不大。
  另一个坏处则是我的三个场景都是在游戏启动时就创建了，所以启动时间会较长，有时间可以想想有没有办法再优化下。
### 4. 降低场景间的耦合性

视频中在主场景构造函数中创建关卡选择场景，也就是在A的代码中创建了B，这样做其实将两个场景类耦合在了一起。

重构后，我在BaseWindow的构造函数中创建三个场景，三个场景是平行的，self-contained的，它们向外提供了信号或接口，每个场景都可以单独拎出来使用，可以灵活的与其它场景对接。
本项目中通过在BaseWindow中使用connect将它们联系起来。
### 5. 快速点击时动画跟不上操作的问题
![image](https://github.com/1944348723/Qt_CoinFlipGame/assets/133476454/e617b728-771d-4e65-b428-605ad835139c)

将关卡图看作矩阵

如果快速点击(1, 1)处和(2,2)处，由于(1,2)和点击的两处都相邻，那么在与(1,1)一起翻转时(2,2)也要翻转，(1,2)该如何响应

我想到以下方案：

①每一个coin对象中设一个操作计数，当需要操作时将其+1，完成后减1，这样最终会将所有操作完成
但问题是动画会有延迟，如果快速点击同一金币，可能点击结束后很久，金币还在翻转，太鬼畜了。

②一次点击的动画完全结束后才能进行下一次点击

在Coin类中包含一个当前正在翻转的金币数的静态成员变量flippingCount，当有一个金币开始翻转时就将其加1，结束时将其减1。当该值大于0时，不允许进行点击操作。
这样做的缺点是，当玩家点击较快时，后续的点击会没有作用，导致操作被吞。
但考虑到在动画完成前进行下一次点击的可能性不是非常大，而且可以将动画速度加快，进一步降低其发生概率，发生了这种情况影响也较小，因此我采用的此方案。

**为什么不设置一个标志位直接标识当前是否有翻转操作呢？**

这种标识设置为有金币在翻转简单，有金币被点击了就可以设置为true。但是在何时设置为false是个问题。
如果设置在翻转函数末尾，由于所有对象是共享成员函数的，那么在任意一个金币翻转结束后都会将该标志设为false，而金币翻转动画的结束时间是不同的，尤其是被点击的金币，最先完成。
当它完成后，将标识设为false时，其实还有相邻的金币在翻转。所以不能这样做。
