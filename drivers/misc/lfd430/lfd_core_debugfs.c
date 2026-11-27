// SPDX-License-Identifier: GPL-2.0
/*
 * lfd_core debugfs view: /sys/kernel/debug/lfd430/sensors
 *
 * Reading the file calls every registered sensor's read() and prints one
 * line per sensor: "<name> <value>" or "<name> error <errno>".
 */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include "lfd_sensor.h"
#include "lfd_core.h"

static struct dentry *lfd_dir;

static int sensors_show(struct seq_file *m, void *unused)
{
	/*
	 * TODO T4: Walk lfd_core_sensors under lfd_core_lock; for each sensor
	 *   call ops->read(), count the read in nreads, and seq_printf()
	 *   "%-16s %d\n" (or "%-16s error %d\n").  If lfd_core_verbose, also
	 *   pr_info() the value.  Why is it safe to call into another module
	 *   here?  (Think about what lfd_sensor_unregister() must wait for.)
	 */

	struct lfd_sensor *pos;
	int val, ret;

	mutex_lock(&lfd_core_lock);

	list_for_each_entry(pos, &lfd_core_sensors, node) {
		ret = pos->ops->read(pos, &val);
		pos->nreads++;

		if (ret) {
			seq_printf(m, "%-16s error %d\n", pos->name, ret);
			if (READ_ONCE(lfd_core_verbose))
				pr_info("%s: read error %d\n", pos->name, ret);
		} else {
			seq_printf(m, "%-16s %d\n", pos->name, val);
			if (READ_ONCE(lfd_core_verbose))
				pr_info("%s = %d\n", pos->name, val);
		}
	}

	mutex_unlock(&lfd_core_lock);
	return 0;
}
DEFINE_SHOW_ATTRIBUTE(sensors);

int lfd_core_debugfs_init(void)
{
	lfd_dir = debugfs_create_dir("lfd430", NULL);
	debugfs_create_file("sensors", 0444, lfd_dir, NULL, &sensors_fops);
	return 0;
}

void lfd_core_debugfs_exit(void)
{
	debugfs_remove_recursive(lfd_dir);
}
