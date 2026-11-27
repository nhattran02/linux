# SPDX-License-Identifier: GPL-2.0
# Lab 01 task T7: in-tree Makefile for drivers/misc/lfd430/.
# TODO T7: Build lfd_core (two objects) when CONFIG_LFD430_CORE is y or m,
#   and lfd_dummy when CONFIG_LFD430_DUMMY is y or m.  obj-$(CONFIG_FOO)
#   expands to obj-y, obj-m or obj- (ignored).  Deck 00, slide 37.
obj-$(CONFIG_LFD430_DUMMY) += lfd_dummy.o
obj-$(CONFIG_LFD430_CORE) += lfd_core.o
lfd_core-y := lfd_core_debugfs.o lfd_core_main.o