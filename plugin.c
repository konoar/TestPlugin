/****************************************************
 *													*
 * plugin.c											*
 *   copyright 2019.05.23 konoar					*
 *													*
 ****************************************************/

#include "common.h"

#include <unistd.h>
#include <stdio.h>

static int AbortFlag = 0;

int PlgMain(int qid)
{

	struct ksQueueRecord rec;

	if (KS_INVALID == ksQueueInit(qid)) {
		return KS_FAIL;
	}

	while (!AbortFlag) {

		if (ksQueueGet(&rec)) {
			printf("OPPRINT: %d\n", rec.bi);
		}

		usleep(500000);

	}

	return KS_SUCCESS;

}

void Abort()
{
	AbortFlag = 1;
}

KS_EXPORT_EPOINT(PlgMain, Abort);

