#!/bin/bash
#清除所有的编译中间文件
echo "set 1:clean libkeyMerlin.a"
rm -rf ./out/target/product/rk3126c/obj/STATIC_LIBRARIES/libkeyMerlin_intermediates
#./out/target/product/rk3126c/obj/STATIC_LIBRARIES/libkeyMerlin_intermediates/libkeyMerlin.a
echo "set 1:clean libShare.so"
rm -rf ./out/target/product/rk3126c/obj/SHARED_LIBRARIES/libShare_intermediates
rm ./out/target/product/rk3126c/obj/lib/libShare.so
rm ./out/target/product/rk3126c/obj/lib/libShare.so.toc
rm ./out/target/product/rk3126c/symbols/system/lib/libShare.so
rm ./out/target/product/rk3126c/system/lib/libShare.so
echo "set 1:clean merlinFunc"
rm -rf ./out/target/product/rk3126c/obj/EXECUTABLES/merlinFunc_intermediates/
rm ./out/target/product/rk3126c/symbols/system/bin/merlinFunc
rm ./out/target/product/rk3126c/system/bin/merlinFunc
#编译项目此工程的方法
一、将此工程拷贝到android sdk的 external目录下
二、清除所有词工程的编译时，生成的中间文件
三、首先编译工程中的静态库；命令是：mmm external/androidProj/lib/lkeyLib/
四、将生成的静态库文件拷贝到工程指定的目录，然后将编译生成的中间文件删除
4.1、拷贝静态库到目标位置：mv ./out/target/product/rk3126c/obj/STATIC_LIBRARIES/libkeyMerlin_intermediates/libkeyMerlin.a ./external/androidProj/lib/libDir/
4.2、将文件权限设置为777: chmod 777 ./external/androidProj/lib/libDir/libkeyMerlin.a
4.3、删除所有的中间文件：./out/target/product/rk3126c/obj/STATIC_LIBRARIES/libkeyMerlin_intermediates
五、编译整个工程
5.1、命令：mmm external/androidProj/


