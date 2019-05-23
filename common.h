#ifndef __COMMON_H__
#define __COMMON_H__

#define EXPORT_EPOINT(__name__) struct vtbl v = { __name__ }

struct vtbl
{
	int (*plgmain)(void);
};

#endif // __COMMON_H__

