#ifndef __BUF_H__
#define __BUF_H__

struct buf {
	int valid;
	volatile int disk;
	//int disk;
	uint dev;
	uint blockno;
	// todo 增加睡眠锁
	// struct sleeplock lock;
	uint refcnt;
	struct buf *prev;
	struct buf *next;
	uchar data[BSIZE];
};

#endif // !__BUF_H__
