#ifndef __PF_DEFINE__H__
#define __PF_DEFINE__H__

#define PF_DEF_BOOT_INFO_RELEASE		"INFO_RELEASE"
#define PF_DEF_BOOT_INFO_VERSION		"INFO_VERSION"
#define PF_DEF_BOOT_INFO_MODEL			"INFO_MODEL"
#define PF_DEF_BOOT_INFO_RESCUE			"RESCUE"

#define PF_DEF_USER_CONFIG_DIR			"/data/config/"
#define PF_DEF_DEFAULT_CONFIG_DIR		"/system/default/"
#define PF_DEF_CONFIG_TMP_DIR			"/tmp/config/"
#define PF_DEF_SCRIPTS_DIR				"/system/scripts/"

#define PF_DEF_UDEV_ID_BUS				"ID_BUS"
#define PF_DEF_UDEV_ID_MODEL			"ID_MODEL"
#define PF_DEF_UDEV_ID_VENDOR			"ID_VENDOR"
#define PF_DEF_UDEV_ID_SERIAL_SHORT		"ID_SERIAL_SHORT"
#define PF_DEF_UDEV_DEVTYPE				"DEVTYPE"
#define PF_DEF_UDEV_DEVPATH				"DEVPATH"
#define PF_DEF_UDEV_ACTION				"ACTION"
#define PF_DEF_UDEV_DEVNAME				"DEVNAME"
#define PF_DEF_UDEV_MAJOR				"MAJOR"
#define PF_DEF_UDEV_MINOR				"MINOR"
#define PF_DEF_UDEV_INTERFACE			"INTERFACE"

#define PF_DEF_SERVICE_PORT_NFS			2049
#define PF_DEF_WATCHDOG_PERIOD			5				// Second
#define PF_DEF_MARK_WATCHDOG_DISABLE	"/tmp/disable_watchdog"

enum EPF_FILESYSTEM_TYPE {
	EPF_FS_UNKNOWN = -1,
	EPF_FS_FAT = 0,
	EPF_FS_EXFAT,
	EPF_FS_NTFS,
	EPF_FS_EXT4,
	EPF_FS_EXT3,
	EPF_FS_EXT2,
	EPF_FS_ISO9660,
	EPF_FS_UDF,
	EPF_FS_FUSEBLK,
	EPF_FS_NFS,
	EPF_FS_END
} ;
typedef enum EPF_FILESYSTEM_TYPE EpfFileSystem ;

enum EPF_CONFIG_TYPE {
	EPF_CONFIG_SYSTEM = 0,
	EPF_CONFIG_NETWORK,
	EPF_CONFIG_RUNTIME,
	EPF_CONFIG_COUNT
} ;
#define PF_CONFIG_MASK(x)			(1<<(x))

#endif /* __PF_DEFINE__H__ */

