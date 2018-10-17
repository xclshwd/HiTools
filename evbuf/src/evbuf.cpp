

#include "evbuf.h"


struct evbuffer *evbuffer_new(void)
{
	struct evbuffer *buffer;
	
	buffer = (struct evbuffer *)calloc(1, sizeof(struct evbuffer));
	
	return (buffer);
}

void evbuffer_free(struct evbuffer *buffer)
{
	if (buffer->orig_buffer != NULL)
	{
		free(buffer->orig_buffer);
	}
	
	free(buffer);
}

/* 
* This is a destructive add.  The data from one buffer moves into
* the other buffer.
*/

#define SWAP(x,y) do { \
	(x)->buffer = (y)->buffer; \
	(x)->orig_buffer = (y)->orig_buffer; \
	(x)->misalign = (y)->misalign; \
	(x)->totallen = (y)->totallen; \
	(x)->off = (y)->off; \
} while (0)


/* Adds data to an event buffer */

// 该函数用于清理 misalign, 空出更多空间
static void evbuffer_align(struct evbuffer *buf)
{
	memmove(buf->orig_buffer, buf->buffer, buf->off);
	buf->buffer = buf->orig_buffer;
	buf->misalign = 0;
}

/* Expands the available space in the event buffer to at least datlen */
// 扩展空间, 用于容纳更多有效数据
int evbuffer_expand(struct evbuffer *buf, size_t datlen)
{
	size_t need = buf->misalign + buf->off + datlen;
	
	/* If we can fit all the data, then we don't have to do anything */
	if (buf->totallen >= need)
	{
		return (0);
	}
	
	/*
	* If the misalignment fulfills our data needs, we just force an
	* alignment to happen.  Afterwards, we have enough space.
	*/
	if (buf->misalign >= datlen) 
	{
		evbuffer_align(buf);
	} 
	else 
	{
		void *newbuf;
		size_t length = buf->totallen;
		/**buf大小最小256字节，翻倍扩展*/
		if (length < 256)
		{
			length = 256;
		}
		
		while (length < need)
		{
			length <<= 1;
		}

		printf("buf ptr=0x%x, buf->totallen =%u , length=%u, need=%u\n", (unsigned int)buf , buf->totallen, length, need);
		if (buf->orig_buffer != buf->buffer)
		{
			evbuffer_align(buf);
		}
		
		if ((newbuf = realloc(buf->buffer, length)) == NULL)
		{
			return (-1);
		}

		return (0);
	
		/*
		* If the misalignment fulfills our data needs, we just force an
		* alignment to happen.  Afterwards, we have enough space.
	*/
	if (buf->misalign >= datlen) 
	{
		evbuffer_align(buf);
	} 
	else 
	{
		void *newbuf;
		size_t length = buf->totallen;
		
		if (length < 256)
			length = 256;
		while (length < need)
			length <<= 1;

		printf("buf ptr=0x%x, buf->totallen =%u , length=%u, need=%u\n", (unsigned int)buf , buf->totallen, length, need);
		if (buf->orig_buffer != buf->buffer)
			evbuffer_align(buf);
		if ((newbuf = realloc(buf->buffer, length)) == NULL)
			return (-1);
		
		buf->orig_buffer = buf->buffer = (unsigned char *)newbuf;
		buf->totallen = length;
	}
	
	return (0);
}

int evbuffer_add(struct evbuffer *buf, const void *data, size_t datlen)
{
	size_t need = buf->misalign + buf->off + datlen;
	
	if (buf->totallen < need) 
	{
		if (evbuffer_expand(buf, datlen) == -1)
		{
			return (-1);
		}

	if (buf->totallen < need) 
	{
		if (evbuffer_expand(buf, datlen) == -1)
		{
			return (-1);
		}

	}
	memcpy(buf->buffer + buf->off, data, datlen);
	buf->off += datlen;
	
	return (0);
}

// 调整evbuf的尺寸, 每次读出或者写入后调用
void evbuffer_drain(struct evbuffer *buf, size_t len)
{
	
	if (len >= buf->off) 
	{

	if (len >= buf->off) 
	{
		buf->off = 0;
		buf->buffer = buf->orig_buffer;
		buf->misalign = 0;
		goto done;
	}
	
	buf->buffer += len;
	buf->misalign += len;
	
	buf->off -= len;
	
done:
	/* Tell someone about changes in this buffer */
//	if (buf->off != oldoff && buf->cb != NULL)
//		(*buf->cb)(buf, oldoff, buf->off, buf->cbarg);
	
	return;
}

/*
* Reads data from a file descriptor into a buffer.
*/

// 下面是evbuf和文件描述符的结合操作

#define EVBUFFER_MAX_READ	4096

int evbuffer_read(struct evbuffer *buf, int fd, int howmuch)
{
	unsigned char *p;
	int n = EVBUFFER_MAX_READ;
	

	if (howmuch < 0 || howmuch > n)
		howmuch = n;
	
	/* If we don't have FIONREAD, we might waste some space here */
	if (evbuffer_expand(buf, howmuch) == -1)
		return (-1);
	
	/* We can append new data at this point */
	p = buf->buffer + buf->off;
	
	n = net_read(fd, p, howmuch);
	if (n == -1)
		return (-1);
	if (n == 0)
		return (0);
	
	buf->off += n;
	
	return (n);
}

int evbuffer_write(struct evbuffer *buffer, int fd)
{
	int n;
	
	n = net_write(fd, buffer->buffer, buffer->off);
	if (n == -1)
		return (-1);
	if (n == 0)
		return (0);
	evbuffer_drain(buffer, n);
	return (n);
}



