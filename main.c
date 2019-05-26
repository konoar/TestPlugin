/****************************************************
 *													*
 * main.c											*
 *   copyright 2019.05.23 konoar					*
 *													*
 ****************************************************/

#include "common.h"

#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define TEST_RECORD_COUNT 12

static struct ksV *v =  0;

void sighandle(int sig)
{

	if (SIGINT == sig && v) {
		printf("\n\n-- Aborted --\n\n");
		v->abort();
	}

}

int main(int argc, char *argv[])
{

	struct ksQueueRecord rec;

	void *hdl =  0;
	int pid, qid, st = 8;

	hdl = dlopen("./plugin.so", RTLD_NOW);

	if (!hdl) {
		return 1;
	}

	v = dlsym(hdl, "v");

	if (!v) {
		return 2;
	}

	qid = ksQueueInit(-1); {

		if (0 > qid) {
			return 4;
		}

		if (0 == (pid = fork())) {
			return v->plgmain(qid);
		}

		if (SIG_ERR != signal(SIGINT, sighandle)) {

			for (int idx = 0; idx < TEST_RECORD_COUNT; idx++) {

				usleep(700000);

				rec.op = KS_OP_PRINT;
				rec.bi = idx + 101;
				rec.bo = 0;
				rec.re = 0;

				ksQueuePut(&rec);

			}

			waitpid(pid, &st, 0);

		}

	} ksQueueUninit(qid);

	return st;

}

