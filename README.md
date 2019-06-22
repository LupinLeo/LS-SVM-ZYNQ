# LS-SVM implemented in ZYNQ

 &nbsp;
## Introduction  
![](https://github.com/LupinLeo/LS-SVM-ZYNQ/blob/master/image/SVM.bmp)

本项目是基于Xlinx的ZYNQ7000系列，实现了最小二乘法支持向量机（LS-SVM）

* 支持向量机模块使用了C++在Vivado HLS工具上实现
* 输入数据较少
* 所有代码经过板上验证


## Envoirment  
* OS: Windows 7
* Vivado 
* Vivado HLS
* Xlinx SDK

## Usage
* HLS_src内是LS-SVM的代码，需要根据自己的板子建立HLS工程，用此文件夹内代码生成IP核。test内是HLS测试代码。
* SDK_src内是ARM部分的代码，在Vivado中根据自己的板子，用生成的IP核搭建系统并生成bit流文件后，lauch SDK创建linux工程编译为elf使用
* 需要板子上linux系统
## test
使用板子实测跑出的参数，在ls-svm.py内画出的超平面如图：

![](https://github.com/LupinLeo/LS-SVM/blob/master/image/LS-SVM.png)

