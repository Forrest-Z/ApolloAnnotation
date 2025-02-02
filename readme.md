# 导论

**本人邮箱：hanhy20@mails.jlu.edu.cn** **欢迎交流**。

基于[**apollo-v6.0.0**](https://github.com/ApolloAuto/apollo/releases/tag/v6.0.0)为其各个模块 以及 **Cyber框架** 的部分源码作了解析和注释

* 在代码上传时，某些大文件(**主要是某些模型文件**)没有上传,下面给出了这些文件的详细路径，如果有需要的，可以去Apollo的github上下载，对应版本**[apollo-v6.0.0](https://github.com/ApolloAuto/apollo/releases/tag/v6.0.0)**

  

```c
*.caffemodel
*.model
*.caffemodel.metadata
*.onnx

modules/planning/data/model/*.pt

modules/perception/production/data/perception/camera/models/lane_detector/darkSCNN/params
modules/perception/production/data/perception/camera/models/lane_detector/darkSCNN/params
modules/perception/production/data/perception/camera/models/yolo_obstacle_detector/3d-r4-half/params
modules/perception/production/data/perception/camera/models/yolo_obstacle_detector/3d-yolo/params
modules/perception/production/data/perception/camera/models/lane_detector/darkSCNN/params
```

## 模块关系

![image-20220112232738411](assets/REDAME.assets/image-20220112232738411.png)



**橙色的部分是正在做的工作。**

**[各个模块订阅及发布的Topic](doc/architecture/topic.md)**

与注释相关的文档，全部保存在**doc文件夹**中(详细内容未上传)，为了便于查找本readme文件会提供相应查找跳转链接。

## 实用工具篇

介绍Cpp常用的一些开源库,如**protobuf glog gflags poco boost ros** 等, 主要涉及他们的安装及基础使用，更加具体的使用在Cyber篇的cyber_cmake源码中会体现。

这些第三方库很多在apollo中会用到, 属于比较常用的实用工具。

## Cyber篇

完成了**Cyber的cmake版移植**，详细代码见**cyber_cmake**

提供了Cyber所需的第三方库的安装脚本,在thritd_party目录下

## 感知篇

针对**感知模块(Perception)**,   [ApolloAnnotation](https://github.com/HaiYangLib/ApolloAnnotation)做了以下工作：

* **Radar子模块**的注释工作主要涉及：Radar**数据预处理**，**IDMatch**和**匈牙利匹配**算法的讲解
* **Liadr子模块**的注释工作主要涉及：Lidar**数据预处理**，**Pointpillars算法**实现过程的分析与代码注释
* **Camera子模块**的注释工作暂时未做

## 预测篇

暂时未做工作

##  **[导航篇](doc/自动驾驶导论.md#导航篇)**



## [规划篇](doc/自动驾驶导论.md#规划篇)

针对**规划模块(Planning)**,   [ApolloAnnotation](https://github.com/HaiYangLib/ApolloAnnotation)做了以下工作：

* 对**Lattice Planner**做了注释工作
* 对**Frenet坐标系**做了推导

 

## 一些心得

向一些愿意分享自动驾驶经验的博主表示感谢：

* **Apollo系列经验**  知乎博主  [王方浩 无人驾驶](https://www.zhihu.com/column/self-driving) 
* **Lattice Planner** B站UP主 [读书思过](https://space.bilibili.com/325034144)
* **路径规划与轨迹跟踪** B站UP主 [小黎的Ally](https://space.bilibili.com/477041559)
* **LQR控制** B站UP主 [忠厚老实的老王](https://space.bilibili.com/287989852?from=search&seid=125495911078972296&spm_id_from=333.337.0.0)
* **官方系列文档** [Apollo开放平台文档](https://apollo.auto/Apollo-Homepage-Document/Apollo_Doc_CN_6_0/)
* **Apollo 3.0阅读笔记**  Github [YannZyl](https://github.com/YannZyl)

