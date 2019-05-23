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

struct QueueRecord
{
	int op;
	int bi;
	int bo;
	int re;
};

extern int QueueInit(int id);
extern int QueuePut(struct QueueRecord *rec);
extern int QueueGet(struct QueueRecord *rec);

#endif // __COMMON_H__

