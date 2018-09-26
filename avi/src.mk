#���ļ��ı�������makefileһ��

#ʹ��gcc���б��롣��Щ�ڿ�Դ������Ͽ����Ĵ���ʹ��g++���б�������һ��Ѿ��棬Ĭ��ʹ��g++���б���,����const char*��char*�໥��ֵ
USE_GCC=n

PROJECT_DIR=$(shell pwd)

#�����⼰����ͷ�ļ�·��
ifndef STREAMAX_CBB
STREAMAX_CBB:=${PROJECT_DIR}/../../release
endif

CFLAGS+=-Os -Wno-unused-variable


#ͷ�ļ�·��
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




#�������ͷ�ļ�
ifeq ($(PRODUCT_TYPE), X5-III)
	INCLUDE_DIR+=
endif

#Դ�ļ�·����makefile��ɨ������·����.c��.cpp�ļ����б���
SRC_DIR+=${PROJECT_DIR}/ManagerMsgClient
SRC_DIR+=${PROJECT_DIR}/Protocol
SRC_DIR+=${PROJECT_DIR}/MediaWork
SRC_DIR+=${PROJECT_DIR}/Session
SRC_DIR+=${PROJECT_DIR}/SocketUtils

#����������Զ�ɨ��Ŀ¼�������·�����Բ��裬ͨ������ֱ�Ӷ�����Ҫ������ļ�
SRC_FILE+=

#��·��
LIB_DIR+=-L${STREAMAX_CBB}/libtoolkit/lib
LIB_DIR+=-L${STREAMAX_CBB}/libcommon/lib
LIB_DIR+=-L${STREAMAX_CBB}/opensource/lib

#������
STATIC_LIB+=
DYN_LIB+=-lremote_operate_file
DYN_LIB+=-lpthread
DYN_LIB+=-ltoolkit
DYN_LIB+=-lSysConfig
#DYN_LIB+=-lftpclient

#Ŀ���ļ���,����׺Ϊ.aʱ����Ϊ��̬��,��׺Ϊ.so
AIM_NAME=N9MSRClient
AIM_NAME_EX=

#������ʱ�����²�������Ҫ������ͷ�ļ�����������Ŀ¼
ifdef RELEASE_DIR
define RELEASE_INCLUDE_FILE
			#@mkdir -p ${RELEASE_DIR}/include
			#@mkdir -p ${RELEASE_DIR}/include/buspad
			#@cp -rf ${PROJECT_DIR}/include/* ${RELEASE_DIR}/include/buspad
endef
endif
