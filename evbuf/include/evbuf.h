
/************************************************************************
高级用户缓冲区, 参考libevent
************************************************************************/

#ifndef __EVBUF_H__
#define __EVBUF_H__

//These functions deal with buffering input and output 
//处理用户缓冲区
struct evbuffer 
{
	unsigned char *buffer;		// 有效数据指针
	unsigned char *orig_buffer;	//缓冲区指针, 用于realloc/free
	
	size_t misalign;		//不可用数据的指针, 指 orig_buffer和buffer的空区
	size_t totallen;		//缓冲区的总长度
	size_t off;			// 有效数据的长度 
};

#define EVBUFFER_LENGTH(x)	((x)->off)
#define EVBUFFER_DATA(x)	(unsigned char *)((x)->buffer)
#define EVBUFFER_INPUT(x)	(x)->input
#define EVBUFFER_OUTPUT(x)	(x)->output


struct evbuffer *evbuffer_new(void);
void evbuffer_free(struct evbuffer *buffer);

int evbuffer_expand(struct evbuffer *buf, size_t datlen);
int evbuffer_add(struct evbuffer *buf, const void *data, size_t datlen);
void evbuffer_drain(struct evbuffer *buf, size_t len);

int evbuffer_read(struct evbuffer *buf, int fd, int howmuch);
int evbuffer_write(struct evbuffer *buffer, int fd);


#endif //__EVBUF_H__

