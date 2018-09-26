#该文件的编译规则和makefile一样

#使用gcc进行编译。有些在开源库基础上开发的代码使用g++进行编译会出现一大堆警告，默认使用g++进行编译,比如const char*和char*相互赋值
USE_GCC=n

PROJECT_DIR=$(shell pwd)

#锐明库及公共头文件路径
ifndef STREAMAX_CBB
STREAMAX_CBB:=${PROJECT_DIR}/../../release
endif

CFLAGS+=-Os -Wno-unused-variable


#头文件路径
INCLUDE_DIR+=-I${PROJECT_DIR}
INCLUDE_DIR+=-I${PROJECT_DIR}/ManagerMsgClient
INCLUDE_DIR+=-I${PROJECT_DIR}/Protocol
INCLUDE_DIR+=-I${PROJECT_DIR}/MediaWork
INCLUDE_DIR+=-I${PROJECT_DIR}/Session
INCLUDE_DIR+=-I${PROJECT_DIR}/SocketUtils
INCLUDE_DIR+=-I${STREAMAX_CBB}/include
INCLUDE_DIR+=-I${STREAMAX_CBB}/libtoolkit/include
INCLUDE_DIR+=-I${STREAMAX_CBB}/libtoolkit/include/i18n
INCLUDE_DIR+=-I${STREAMAX_CBB}/libtoolkit/include/message
INCLUDE_DIR+=-I${STREAMAX_CBB}/libtoolkit/include/md5
INCLUDE_DIR+=-I${STREAMAX_CBB}/sdk/include
INCLUDE_DIR+=-I${STREAMAX_CBB}/libcommon/include
#INCLUDE_DIR+=-I${STREAMAX_CBB}/opensource/include/ftpclient




#机型相关头文件
ifeq ($(PRODUCT_TYPE), X5-III)
	INCLUDE_DIR+=
endif

#源文件路径，makefile会扫描以下路径的.c和.cpp文件进行编译
SRC_DIR+=${PROJECT_DIR}/ManagerMsgClient
SRC_DIR+=${PROJECT_DIR}/Protocol
SRC_DIR+=${PROJECT_DIR}/MediaWork
SRC_DIR+=${PROJECT_DIR}/Session
SRC_DIR+=${PROJECT_DIR}/SocketUtils

#如果不期望自动扫描目录，上面的路径可以不设，通过以下直接定义需要编译的文件
SRC_FILE+=

#库路径
LIB_DIR+=-L${STREAMAX_CBB}/libtoolkit/lib
LIB_DIR+=-L${STREAMAX_CBB}/libcommon/lib
LIB_DIR+=-L${STREAMAX_CBB}/opensource/lib

#依赖库
STATIC_LIB+=
DYN_LIB+=-lremote_operate_file
DYN_LIB+=-lpthread
DYN_LIB+=-ltoolkit
DYN_LIB+=-lSysConfig
#DYN_LIB+=-lftpclient

#目标文件名,当后缀为.a时编译为静态库,后缀为.so
AIM_NAME=N9MSRClient
AIM_NAME_EX=

#发布库时，以下操作将需要发布的头文件拷贝到发布目录
ifdef RELEASE_DIR
define RELEASE_INCLUDE_FILE
			#@mkdir -p ${RELEASE_DIR}/include
			#@mkdir -p ${RELEASE_DIR}/include/buspad
			#@cp -rf ${PROJECT_DIR}/include/* ${RELEASE_DIR}/include/buspad
endef
endif
