/******************************************************************* 
 *  Copyright(c) 2018-- 
 *  All rights reserved. 
 *   
 *  文件名称: 公共数据类型定义
 *  简要描述: 
 *   
 *  当前版本:1.0 
 *  作者: shliu
 *  日期: 2018-10-15
 *  说明: 

 ******************************************************************/

#ifndef __CM_BITS_H_
#define __CM_BITS_H_
 
 /** void pointer. */
typedef void *cm_pvoid_t;

/** Signed 64bit integer. */
typedef long long  cm_int64_t;

/** Unsigned 64bit integer. */
typedef unsigned long long   cm_uint64_t;

/** Signed 32bit integer. */
typedef int     cm_int32_t;

/** Unsigned 32bit integer. */
typedef unsigned int    cm_uint32_t;

/** Signed 16bit integer. */
typedef short       cm_int16_t;

/** Unsigned 16bit integer. */
typedef unsigned short  cm_uint16_t;

/** Signed 8bit integer. */
typedef signed char cm_int8_t;

/** Unsigned 8bit integer. */
typedef unsigned char   cm_uint8_t;

/** status. */
#define CM_SUCCESS  (0)
#define CM_FAIL     (-1)

#define CM_FALSE    (0)
#define CM_TRUE     (!CM_FALSE)

/**base*/
#define CM_MIN(a, b)				((a) < (b) ? (a) : (b))
#define CM_MAX(a, b)				((a) < (b) ? (b) : (a))
#define CM_BETWEEN(x, a, b)			((a) <= (x) && (x) <= (b))
#define CM_DIVCEIL(n, d)			(((n) + ((d) - 1)) / (d))
#define CM_LIMIT(x, a, b)			((x) = (x) < (a) ? (a) : (x) > (b) ? (b) : (x))

#define CM_ARRAY_LEN(a)				(sizeof(a) / sizeof(a)[0])
#define CM_ALIGN_BACK(x, a) 		((a) * (((x) / (a))))
#define CM_ALIGN_UP(x, a)   		((a) * ((x+a-1)/(a)))

/**bits macro*/
#define CM_BIT_TEST(val,offset) 	(((val) & (1ll<<offset))!=0)

#define CM_BIT_SET(val,offset) 		(((val) |= (1ll<<offset)))

#define CM_BIT_CLR(val,offset) 		(((val) &= ~(1ll<<offset)))


/**little Endian*/
	
#define CM_PUT8(p, value) 	((p)[0] = (cm_uint8_t)((value)>>0)&0xff)

#define CM_GET8(p) 			((p)[0])


#define CM_PUTLE16(p, value)  ((p)[0] = ((cm_uint16_t)(value)>>0)&0xff, (p)[1] = ((cm_uint16_t)(value)>>8)&0xff)
						  
#define CM_PUTLE32(p, value)  (\
								(p)[0] = (cm_uint8_t)((cm_uint32_t)(value)>>0)&0xff, (p)[1] = (cm_uint8_t)((cm_uint32_t)(value)>>8)&0xff, \
								(p)[2] = (cm_uint8_t)((cm_uint32_t)(value)>>16)&0xff,(p)[3] = (cm_uint8_t)((cm_uint32_t)(value)>>24)&0xff \
							)
						  

#define CM_PUTLE64(p, value) ( \
								(p)[0] = (cm_uint8_t)((cm_uint64_t)(value)>>0)&0xff, 	(p)[1] = (cm_uint8_t)((cm_uint64_t)(value)>>8)&0xff, \
								(p)[2] = (cm_uint8_t)((cm_uint64_t)(value)>>16)&0xff,	(p)[3] = (cm_uint8_t)((cm_uint64_t)(value)>>24)&0xff,\
								(p)[4] = (cm_uint8_t)((cm_uint64_t)(value)>>32)&0xff,   (p)[5] = (cm_uint8_t)((cm_uint64_t)(value)>>40)&0xff,\
								(p)[6] = (cm_uint8_t)((cm_uint64_t)(value)>>48)&0xff,	(p)[7] = (cm_uint8_t)((cm_uint64_t)(value)>>56)&0xff\
							)
							
#define CM_GETLE16(p) 		(((cm_uint8_t)(p)[0] << 0) | ((cm_uint8_t)(p)[1] << 8))
							
#define CM_GETLE32(p) 		( \
								((cm_uint8_t)(p)[0] << 0) | ((cm_uint8_t)(p)[1] << 8) | \
								((cm_uint8_t)(p)[2] << 16)| ((cm_uint8_t)(p)[3] << 24)  \
							)
							
#define CM_GETLE64(p) 		( \
								((cm_uint64_t)(p)[0] << 0)  |  ((cm_uint64_t)(p)[1] << 8) |  \
								((cm_uint64_t)(p)[2] << 16) | ((cm_uint64_t)(p)[3] << 24) | \
								((cm_uint64_t)(p)[4] << 32) | ((cm_uint64_t)(p)[5] << 40) |\
								((cm_uint64_t)(p)[6] << 48) | ((cm_uint64_t)(p)[7] << 56)	\
							)

/**big Endian*/
#define CM_PUTBE16(p, value) ( (p)[0] = ((cm_uint16_t)(value)>>8)&0xff, (p)[1] = ((cm_uint16_t)(value)>>0)&0xff )
							
#define CM_PUTBE32(p, value) ( \
								(p)[0] = (cm_uint8_t)((cm_uint32_t)(value)>>24)&0xff, (p)[1] = (cm_uint8_t)((cm_uint32_t)(value)>>16)&0xff, \
								(p)[2] = (cm_uint8_t)((cm_uint32_t)(value)>>8)&0xff,  (p)[3] = (cm_uint8_t)((cm_uint32_t)(value)>>0)&0xff \
							)
							
#define CM_PUTBE64(p, value) ( \
								(p)[0] = (cm_uint8_t)((cm_uint64_t)(value)>>56)&0xff, (p)[1] = (cm_uint8_t)((cm_uint64_t)(value)>>48)&0xff, \
								(p)[2] = (cm_uint8_t)((cm_uint64_t)(value)>>40)&0xff, (p)[3] = (cm_uint8_t)((cm_uint64_t)(value)>>32)&0xff, \
								(p)[4] = (cm_uint8_t)((cm_uint64_t)(value)>>24)&0xff, (p)[5] = (cm_uint8_t)((cm_uint64_t)(value)>>16)&0xff, \
								(p)[6] = (cm_uint8_t)((cm_uint64_t)(value)>>8)&0xff,  (p)[7] = (cm_uint8_t)((cm_uint64_t)(value)>>0)&0xff \
							)

#define CM_GETBE16(p) 	( ((cm_uint8_t)(p)[0] << 8) | ((cm_uint8_t)(p)[1] << 0))
						
#define CM_GETBE32(p)   (\
							((cm_uint8_t)(p)[0] << 24) | ((cm_uint8_t)(p)[1] << 16) | \
							((cm_uint8_t)(p)[2] << 8) | ((cm_uint8_t)(p)[3] << 0)\
						)
						
#define CM_GETBE64(p) 	( \
							((cm_uint64_t)(p)[0] << 56) | ((cm_uint64_t)(p)[1] << 48) | \
							((cm_uint64_t)(p)[2] << 40) | ((cm_uint64_t)(p)[3] << 32) | \
							((cm_uint64_t)(p)[4] << 24) | ((cm_uint64_t)(p)[5] << 16) | \
							((cm_uint64_t)(p)[6] << 8) | ((cm_uint64_t)(p)[7] << 0) \
						)

/**free delete close*/

#define CM_SAFE_FREE_(ptr) do{\
        if(ptr != NULL)\
        {\
            free(ptr);\
            ptr = NULL;\
        }\
    }while(0)


#define CM_SAFE_DELETE_(ptr) do{\
        if(ptr != NULL)\
        {\
            delete ptr;\
            ptr = NULL;\
        }\
    }while(0)


#define CM_SAFE_DELETE_ARRAY_(ptr) do{\
        if(ptr != NULL)\
        {\
            delete []ptr;\
            ptr = NULL;\
        }\
    }while(0)


#define CM_SAFE_CLOSE_(fd) do{\
        if(fd >= 0)\
        {\
            close(fd);\
            fd = -1;\
        }\
    }while(0)


#define CM_SAFE_FCLOSE_(fp) do{\
        if(fp != NULL)\
        {\
            fclose(fp);\
            fp = NULL;\
        }\
    }while(0)


#define CM_POINTER_ASSIGNMENT_(ptr, value) do{\
    if(ptr != NULL)\
    {\
        *ptr = value;\
    }\
}while(0)
						

#endif//__CM_BITS_H_
