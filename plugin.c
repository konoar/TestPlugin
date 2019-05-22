#include <stdio.h>
#include "common.h"

void hello()
{

	printf("Hello Plugin!\n");

}

struct vtbl v = { hello };

