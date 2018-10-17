
/************************************************************************
�߼��û�������, �ο�libevent
************************************************************************/

#ifndef __EVBUF_H__
#define __EVBUF_H__

//These functions deal with buffering input and output 
//�����û�������
struct evbuffer 
{
	unsigned char *buffer;		// ��Ч����ָ��
	unsigned char *orig_buffer;	//������ָ��, ����realloc/free
	
	size_t misalign;		//���������ݵ�ָ��, ָ orig_buffer��buffer�Ŀ���
	size_t totallen;		//���������ܳ���
	size_t off;			// ��Ч���ݵĳ��� 
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

