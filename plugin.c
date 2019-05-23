#include <stdio.h>
#include <unistd.h>
#include "common.h"

int hello()
{

	for (int idx = 0; idx < 30; idx++) {
		printf("Hello Plugin!\n");
		usleep(500000);
	}

	return 0;

}

EXPORT_EPOINT(hello);

