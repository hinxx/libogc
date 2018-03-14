#ifndef __DEBUG_IF_H__
#define __DEBUG_IF_H__

#include <gctypes.h>

#define DBG_LOGGING

#ifdef DBG_LOGGING
static char* __basename(char *path)
{
	s32 i;

	for (i = strlen(path) - 1; i >= 0; i--)
	{
		if (path[i] == '/')
			return path + i + 1;
	}
	return path;
}

#define DBG_LOG(fmt, args...) \
	do { \
		fprintf(stderr, "%s: %s:%d:" fmt, __basename(__FILE__), __FUNCTION__, __LINE__, ##args); \
	} while (0)
#else
#define DBG_LOG(fmt, args...) do { } while (0)
#endif // DBG_LOGGING

#define GDBSTUB_DEVICE_USB		0
#define GDBSTUB_DEVICE_TCP		1

struct dbginterface
{
	s32 fhndl;

	int (*open)(struct dbginterface *device);
	int (*close)(struct dbginterface *device);
	int (*wait)(struct dbginterface *device);
	int (*read)(struct dbginterface *device,void *buffer,int size);
	int (*write)(struct dbginterface *devicec,const void *buffer,int size);
};

#endif
