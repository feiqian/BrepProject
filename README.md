**This project is written to construct a simple brep-based model**

####输入格式（.brp文件）
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

欧拉操作操作符：  
```
0 -> mvfs  
1 -> mev  
2 -> mef  
3 -> kemr  
4 -> kfmrh  
5 -> select loop  
6 -> sweep
```

示例：

cube.brp：sweep+5个欧拉操作实现的两个孔的立方体  
cube2.brp:5个欧拉操作实现的带一个孔的立方体

####操作
使用enter键切换实体表示和线框表示