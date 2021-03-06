
#ifndef __PFWATCHDOG_H__
#define __PFWATCHDOG_H__

#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include "pftype.h"
#include "pflimit.h"

/*****************************************************************************
 WatchDog ID
 +--------+--------+----------------+
 |  (1)   |  (2)   |      (3)       |
 +--------+--------+----------------+

 (1) : type - 8 bits
 (2) : reserved - 12 bits
 (3) : size - 12 bits

*****************************************************************************/

#define PFWD_QUEUE_NAME				"q.watchdog"
#define PFWD_DEFAULT_TIMEOUT		(30)
#define PFWD_DEFAULT_ALIVE_TIMEOUT	(5)
#define PFWD_TYPE(id)				(((id)>>24) & 0xff)
#define PFWD_PAYLOAD_SIZE(id)		((id) & 0xfff)
#define PFWD_INIT(wd, id)		\
	do {						\
		(wd)->wdid = id;		\
		(wd)->pid = getpid();	\
	} while (0)

#define __MKWDID(wdt,size)		((wdt)<<24|(size&0xfff))
#define MKWDID(wdt,type)		__MKWDID(wdt,sizeof(type))

#define __PFWD_STRUCT__			uint32_t wdid; pid_t pid; char name[MAX_NAME_LENGTH];

enum EPFWD_COMMAND_TYPE {
	EPFWD_CMD_REGISTER			= 0x63,
	EPFWD_CMD_UNREGISTER,
	EPFWD_CMD_START,
	EPFWD_CMD_STOP,
	EPFWD_CMD_ALIVE,
	EPFWD_CMD_SUBREGISTER,
	EPFWD_CMD_SUBUNREGISTER,
	EPFWD_CMD_SUBALIVE,
	EPFWD_CMD_END
};
typedef enum EPFWD_MODE_TYPE {
	EPFWD_MODE_NONE				= 0,
	EPFWD_MODE_RESTART,
	EPFWD_MODE_REBOOT,
	EPFWD_MODE_END
} EPfWDMode ;

struct PFWatchdog {
	__PFWD_STRUCT__;
};

struct PFWDRegister {
	__PFWD_STRUCT__;
	char		params[MAX_PARAM_LENGTH];
	uint32_t	eMode;							/* emode_vmmd */
	uint32_t	timeout;
};

struct PFWDUnregister {
	__PFWD_STRUCT__;
};

struct PFWDStart {
	__PFWD_STRUCT__;
};

struct PFWDStop {
	__PFWD_STRUCT__;
};

struct PFWDAlive {
	__PFWD_STRUCT__;
};

struct PFWDSubRegister {
	__PFWD_STRUCT__;
	uint32_t	subId;
	uint32_t	timeout;
};

struct PFWDSubUnregister {
	__PFWD_STRUCT__;
	uint32_t	subId;
};

struct PFWDSubAlive {
	__PFWD_STRUCT__;
	uint32_t	subId;
};

#define PFWD_REGISTER		MKWDID(EPFWD_CMD_REGISTER,		struct PFWDRegister)
#define PFWD_UNREGISTER		MKWDID(EPFWD_CMD_UNREGISTER,	struct PFWDUnregister)
#define PFWD_START			MKWDID(EPFWD_CMD_START,			struct PFWDStart)
#define PFWD_STOP			MKWDID(EPFWD_CMD_STOP,			struct PFWDStop)
#define PFWD_ALIVE			MKWDID(EPFWD_CMD_ALIVE,			struct PFWDAlive)
#define PFWD_SUB_REGISTER	MKWDID(EPFWD_CMD_SUBREGISTER,	struct PFWDSubRegister)
#define PFWD_SUB_UNREGISTER	MKWDID(EPFWD_CMD_SUBUNREGISTER,	struct PFWDSubUnregister)
#define PFWD_SUB_ALIVE		MKWDID(EPFWD_CMD_SUBALIVE,		struct PFWDSubAlive)

#endif /* __PFWATCHDOG_H__ */
