##运行环境
VS2010 + OpenGl

##输入格式
格式为自定义的``brp格式：
```
顶点数目M 欧拉操作数目N
（接下来M个顶点坐标）
x y z
....
....
....
（接下来N个欧拉操作）
操作符 操作数
....
....
....
```

####操作符：
```
0 -> mvfs
1 -> mev
2 -> mef
3 -> kemr
4 -> kfmr
5 -> select loop
6 -> sweep
```

####示例：
程序默认使用``BrepProject.exe``所在目录的``cube.brp``文件，也可以**BrepProject.exe后跟指定的输入文件运行**
- cube.brp：sweep+5个欧拉操作实现的两个孔的立方体
- cube2.brp：5个欧拉操作实现的带一个孔的立方体

##欧拉操作API
    /*
     *构造一个体，面，外环，顶点
     *@param[in] point 新顶点的位置
     *@param[out] solid 新生成的体
     *@return 新生成的顶点
     */
    Vertex* EulerOperator::mvfs(Point point,Solid*& solid)

    /*
     *构造一个位置为point的新的顶点，并构造vertex指向新顶点的边
     *@param[in] vertex 顶点
     *@param[in] point 新生成的顶点位置
     *@param[in] loop 当前环
     *@return 新生成的半边
     */
    Half_Edge* EulerOperator::mev(Vertex* vertex,Point point,Loop* loop)

    /*
     *构造顶点ve1到ve2的一条边，同时构造一个新面
     *注意当前loop的走向变为ve1->ve2,新面loop的走向为ve2->ve1
     *@param[in] ve1 顶点1
     *@param[in] ve2 顶点2
     *@param[in] loop 当前环
     *@return 新生成的面
     */
    Face* EulerOperator::mef(Vertex* ve1,Vertex* ve2,Loop* loop)

    /*
     *删除环中ve1->ve2的一条边，构造一个新环
     *@param[in] ve1 顶点1
     *@param[in] ve2 顶点2
     *@param[in] loop 当前环
     *@return 新生成的环
     */
    Loop* EulerOperator::kemr(Vertex *ve1, Vertex *ve2, Loop *loop)

    /*
     *删除innerLoop指向的面，将其变成outerLoop指向面的内环
     *@param[in] outerLoop 接收删除面的外环
     *@param[in] innerLoop 要删除面所在的外环
     */
    void EulerOperator::kfmrh(Loop* outerLoop,Loop* innerLoop)

    /*
     *平移扫成
     *@param[in] face 要平移的面
     *@param[in] dir 平移方向
     *@param[in] distance 平移方向上的位移
     */
    void EulerOperator::sweep(Face *face, double dir[3], double distance)

##注意事项：
每一个新生成的环都会被顺序存储在一个List当中。程序会有一个默认的当前环（开始时为NULL，在mvfs后自动使用其新生成的外环作当前环）作为某些欧拉操作的输入参数，这样就不用在输入文件的欧拉操作中指定环。当需要指定另一个环作为默认环时，请在输入文件中用**5后面跟要切换环在List中的下标进行指定**。

##操作
- 使用鼠标旋转物体
- 使用enter键切换实体表示和线框表示