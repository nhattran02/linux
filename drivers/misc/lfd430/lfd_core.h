/* SPDX-License-Identifier: GPL-2.0 */
/* Internal declarations shared by the two source files of lfd_core.ko. */
#ifndef LFD_CORE_H
#define LFD_CORE_H

#include <linux/mutex.h>
#include <linux/list.h>

extern struct mutex lfd_core_lock;	/* protects lfd_core_sensors */
extern struct list_head lfd_core_sensors;
extern bool lfd_core_verbose;

int lfd_core_debugfs_init(void);
void lfd_core_debugfs_exit(void);

#endif /* LFD_CORE_H */
