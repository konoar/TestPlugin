/****************************************************
 *													*
 * common.c											*
 *   copyright 2019.05.23 konoar					*
 *													*
 ****************************************************/

#include "common.h"

#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define KS_QUEUE_SIZE 5

static struct ksQueueInfo
{
	long cn;
	long st;
	long ed;
	long mt;
} *Info = 0;

static void *BaseAddr = 0;

static unsigned int ksQueueCalcShmSize()
{

	unsigned int pagesize, vali;
	double vald;

	pagesize = sysconf(_SC_PAGESIZE);

	vald = (double)(sizeof(struct ksQueueInfo) +
		sizeof(struct ksQueueRecord) * KS_QUEUE_SIZE) / pagesize;

	vali = (unsigned int)(vald);

	if ((double)(vali) == vald) {
		return pagesize * vali;
	}

	return pagesize * (vali + 1);

}

static int ksQueueMutexInit()
{

	pthread_mutexattr_t attr;

	if (!Info) {
		return KS_FAIL;
	}

	pthread_mutexattr_init(&attr);

	if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
		return KS_FAIL;
	}

	pthread_mutex_init((pthread_mutex_t*)(&Info->mt), &attr);

	return KS_SUCCESS;

}

static int ksQueueMutexUninit()
{

	if (!Info) {
		return KS_FAIL;
	}

	return KS_SUCCESS;

}

static int ksQueueInitShmGet(int id)
{

	BaseAddr	= shmat(id, NULL, 0);

	Info		= (struct ksQueueInfo*)(BaseAddr);
	Info->cn	= 0;
	Info->st	= 0;
	Info->ed	= 0;

	return id;

}

static int ksQueueInitShmCreate()
{

	int id = shmget(IPC_PRIVATE, ksQueueCalcShmSize(), IPC_CREAT | 0666);

	if (id < 0) {
		return KS_INVALID;
	}

	if (id != ksQueueInitShmGet(id)) {
		return KS_INVALID;
	}

	if (KS_SUCCESS != ksQueueMutexInit()) {
		shmctl(id, IPC_RMID, NULL);
		return KS_INVALID;
	}

	return id;

}

int ksQueueInit(int id)
{

	if (id < 0) {
		return ksQueueInitShmCreate();
	} else {
		return ksQueueInitShmGet(id);
	}

}

int ksQueueUninit(int id)
{

	if (id < 0) {
		return KS_FAIL;
	}

	ksQueueMutexUninit();

	shmctl(id, IPC_RMID, NULL);

	return KS_SUCCESS;

}

int ksQueuePut(struct ksQueueRecord *rec)
{

	struct ksQueueRecord *tgt;

	if (!Info || Info->cn >= KS_QUEUE_SIZE) {
		return KS_FAIL;
	}

	pthread_mutex_lock((pthread_mutex_t*)&Info->mt); {

		tgt = (struct ksQueueRecord*)(BaseAddr + sizeof(struct ksQueueInfo) +
			sizeof(struct ksQueueRecord) * Info->ed);

		if (Info->ed == (KS_QUEUE_SIZE - 1))	Info->ed = 0;
		else									Info->ed = Info->ed + 1;

		if (rec) {
			tgt->op = rec->op;
			tgt->bi = rec->bi;
			tgt->bo = rec->bo;
		} else {
			tgt->op = KS_OP_TERM;
			tgt->bi = 0;
			tgt->bo = 0;
		}

		tgt->re = 0;

		Info->cn = Info->cn + 1;

	} pthread_mutex_unlock((pthread_mutex_t*)&Info->mt);

	return KS_SUCCESS;

}

int ksQueueGet(struct ksQueueRecord *rec)
{

	struct ksQueueRecord *tgt;

	if (!Info || Info->cn == 0) {
		return KS_FAIL;
	}

	pthread_mutex_lock((pthread_mutex_t*)&Info->mt); {

		tgt = (struct ksQueueRecord*)(BaseAddr + sizeof(struct ksQueueInfo) +
			sizeof(struct ksQueueRecord) * Info->st);

		if (Info->st == (KS_QUEUE_SIZE - 1))	Info->st = 0;
		else									Info->st = Info->st + 1;

		Info->cn = Info->cn - 1;

		if (rec) {
			rec->op = tgt->op;
			rec->bi = tgt->bi;
			rec->bo = tgt->bo;
			rec->re = tgt->re;
		}

	} pthread_mutex_unlock((pthread_mutex_t*)&Info->mt);

	return KS_SUCCESS;

}

