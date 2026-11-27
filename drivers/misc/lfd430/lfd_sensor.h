/* SPDX-License-Identifier: GPL-2.0 */
/*
 * API of the lfd_core sensor registry (LFD430 Lab 01).
 *
 * Providers embed a struct lfd_sensor in their own state, fill in name,
 * ops and owner, and register it.  lfd_core calls ops->read() whenever
 * someone reads /sys/kernel/debug/lfd430/sensors.
 */
#ifndef LFD_SENSOR_H
#define LFD_SENSOR_H

#include <linux/list.h>
#include <linux/module.h>

struct lfd_sensor;

struct lfd_sensor_ops {
	/* Store the current value in *val; return 0 or a negative errno. */
	int (*read)(struct lfd_sensor *s, int *val);
};

struct lfd_sensor {
	const char *name;
	const struct lfd_sensor_ops *ops;
	struct module *owner;
	void *priv;

	/* Private to lfd_core: */
	struct list_head node;
	unsigned long nreads;
};

int lfd_sensor_register(struct lfd_sensor *s);
void lfd_sensor_unregister(struct lfd_sensor *s);

#endif /* LFD_SENSOR_H */
