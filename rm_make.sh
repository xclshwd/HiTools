#!/bin/bash

_DEF_FILE_PATH_=$(pwd)/defines

if [ -f ${_DEF_FILE_PATH_} ]; then
  rm ${_DEF_FILE_PATH_}
fi

echo "export RELEASE_ROOT_DIR:=$(pwd)/release" >> $_DEF_FILE_PATH_;

PRODUCT_LIST=(
"X1(3515c)"
"X3(3520d)"
"X5_III(3521)"
"X7(3531)"
"X7_NVR(3535)"
"ES4206(3520dv300)"
"ES8412(3521a)"
"XMD3104(3520dv300)"
"A5_II(3515)"
"A5_III(3521)"
"A5_AHD(3521a)"
"D5(3520d)"
"D5-3.5(3520dv300)"
"D5M-3.5(3515c)"
"6AI_AV12(3515)"
"6AII_AV3(3535)"
"6AII_AV12(3521a)"
"T2(3535)"
"T5(3535)"
"T6(3535)"
"M0026(3520dv300)"
"P1(3520dv300)"
"712_VA(3518c)"
"712_VB(3518c)"
"712_VC(3518c)"
"712_VD(3518c)"
"712_VE(3518c)"
"712_VF(3518c)"
"714_VA(3518c)"
"714_VB(3518c)"
"718_VA(3518ev200)"
"913_VA(3516c)"
"913_VB(3516cv200)"
"916_VA(3516a)"
"920_VA(3516a)"
"A19_VA(3519)"
"N2400(3536a)"
)
echo "product:"
for i in "${!PRODUCT_LIST[@]}"; do
	echo "$i: ${PRODUCT_LIST[$i]}"
done
echo -ne "please input product id:"
read _product_;

if [ "${_product_}" -lt "${#PRODUCT_LIST[@]}" ];then
	PRODUCT_TYPE=${PRODUCT_LIST[${_product_}]%(*}
	echo "export PRODUCT_TYPE:=${PRODUCT_TYPE}" >> $_DEF_FILE_PATH_;

	for c in ${PRODUCT_TYPE}
	do
		case $c in
		  X1 | D5M-3.5 | X3 | D5 | X5_III | A5_III | X7 | 6AII_AV3 | T2 | T5 | T6 | 712_VA | 712_VB | 712_VC | 712_VD | 712_VE | 712_VF | 714_VA | 714_VB | 913_VA | 916_VA | 920_VA)
		    echo "export CROSS_COMPILER:=arm-hisiv100nptl-linux-" >> $_DEF_FILE_PATH_;
		    echo "export COMPILER_NAME:=arm-hisiv100nptl" >> $_DEF_FILE_PATH_;
		    ;;
		  ES4206 | ES8412 | XMD3104 | A5_AHD | D5-3.5 | 6AII_AV12 | M0026 | P1)
		    echo "export CROSS_COMPILER:=arm-hisiv300-linux-" >> $_DEF_FILE_PATH_;
		    echo "export COMPILER_NAME:=arm-hisiv300" >> $_DEF_FILE_PATH_;
		    echo "export CFLAGS=-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations" >> $_DEF_FILE_PATH_;
		    echo "export SDK_DIR:=$(pwd)/SDK/3521a" >> $_DEF_FILE_PATH_;
		    ;;
		  A5_II | 6AI_AV12)
		    echo "export CROSS_COMPILER:=arm-hismall-linux-" >> $_DEF_FILE_PATH_;
		    echo "export COMPILER_NAME:=arm-hismall" >> $_DEF_FILE_PATH_;
		    ;;
		  718_VA | 913_VB)
		    echo "export CROSS_COMPILER:=arm-hisiv300-linux-uclibcgnueabi-" >> $_DEF_FILE_PATH_;
		    echo "export COMPILER_NAME:=arm-hisiv300-1" >> $_DEF_FILE_PATH_;
		    echo "export CFLAGS=-mcpu=arm926ej-s -mno-unaligned-access -fno-aggressive-loop-optimizations" >> $_DEF_FILE_PATH_;
		    ;;
		  N2400)
		    echo "export CROSS_COMPILER:=arm-hisiv400-linux-gnueabi-" >> $_DEF_FILE_PATH_;
		    echo "export COMPILER_NAME:=arm-hisiv400" >> $_DEF_FILE_PATH_;
		    echo "export CFLAGS=-march=armv7-a -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations" >> $_DEF_FILE_PATH_;
		    ;;
		  A19_VA)
		    echo "-----------A19_VA----------";
		    ;;
		  *)
		    echo "invalid product:${PRODUCT_TYPE}";	
		    ;;
		esac
	done
else
	echo "invalid product!"
	exit 1
fi

echo "version type:";
echo " 1: release";
echo " 2: debug";
echo -ne "please input version type id:"
read _version_;

if [ "$_version_" = "2" ];then
	echo "export DEBUG_VERSION:=y" >> $_DEF_FILE_PATH_;
else
	echo "export DEBUG_VERSION:=n" >> $_DEF_FILE_PATH_;
fi

make clean;make
