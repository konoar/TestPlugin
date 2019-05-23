#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include "common.h"

int main(int argc, char *argv[])
{

	struct vtbl *v =  0;
	void *hdl      =  0;
	int pid, status;

	hdl = dlopen("./plugin.so", RTLD_NOW);

	if (!hdl) {
		return 1;
	}

	v = dlsym(hdl, "v");

	if (!v) {
		return 2;
	}

	if (0 == (pid = fork())) {
		return v->plgmain();
	}

	waitpid(pid, &status, 0);
	printf("Main END.\n");

	return 0;

}

