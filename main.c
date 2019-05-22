#include <stdio.h>
#include <dlfcn.h>
#include "common.h"

int main(int argc, char *argv[])
{

	struct vtbl *v = 0;
	void *hdl      = 0;

	hdl = dlopen("./plugin.so", RTLD_NOW);

	if (!hdl) {
		return 1;
	}

	v = dlsym(hdl, "v");

	if (!v) {
		return 2;
	}

	v->plgmain();

	return 0;

}

