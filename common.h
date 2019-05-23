#ifndef __COMMON_H__
#define __COMMON_H__

#define EXPORT_EPOINT(__name__) \
	struct vtbl v = { __name__ }

enum OpCode
{
	OP_PRINT,
};

struct vtbl
{
	int (*plgmain)(void);
};

struct Record
{
	int op;
	int bi;
	int bo;
	int reserved;
};

extern int QueueInit(int id);
extern int QueuePut(struct Record *rec);
extern int QueueGet(struct Record *rec);

#endif // __COMMON_H__

