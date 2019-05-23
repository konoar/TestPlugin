#include "common.h"
#include <sys/shm.h>

struct QueueInfo
{
	long ad;
	long st;
	long ed;
	long cn;
} *info;

static int QueueInitShmCreate()
{

	return 0;

}

static int QueueInitShmGet()
{

	return 0;

}

int QueueInit(int id)
{

	if (id < 0) {
		return QueueInitShmCreate();
	} else {
		return QueueInitShmGet();
	}

}

int QueuePut(struct QueueRecord *rec)
{

	return 0;

}

int QueueGet(struct QueueRecord *rec)
{

	return 0;

}
