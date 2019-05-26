/****************************************************
 *													*
 * common.h											*
 *   copyright 2019.05.23 konoar					*
 *													*
 ****************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#define KS_EXPORT_EPOINT(__plgmain__, __abort__) \
	struct ksV v = { __plgmain__, __abort__ }

#define KS_SUCCESS	 1
#define KS_FAIL		 0
#define KS_INVALID	-1

enum ksOpCode
{
	KS_OP_PRINT,
	KS_OP_TERM,
};

struct ksV
{
	int (*plgmain)(int);
	void (*abort)(void);
};

struct ksQueueRecord
{
	int op;
	int bi;
	int bo;
	int re;
};

extern int ksQueueInit(int id);
extern int ksQueueUninit(int id);
extern int ksQueuePut(struct ksQueueRecord *rec);
extern int ksQueueGet(struct ksQueueRecord *rec);

#endif // __COMMON_H__

