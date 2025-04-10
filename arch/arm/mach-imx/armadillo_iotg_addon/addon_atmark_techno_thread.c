// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2024 Atmark Techno, Inc. All Rights Reserved.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_fdt.h>

#include "armadillo_iotg_std_addon.h"

extern_dtb(addon_atmark_techno_thread_iotg_g3_intf1);
extern_dtb(addon_atmark_techno_thread_iotg_g3_intf2);
extern_dtb(addon_atmark_techno_thread_x1_intf1);

int addon_setup_atmark_techno_thread(struct addon_device *adev)
{
	struct armadillo_iotg_addon *addon = to_addon(adev);
	void *begin;
	size_t size;

	switch (adev->intf) {
	case ADDON_INTERFACE1:
		switch (addon->type) {
		case ADDON_BOARD_TYPE_IOTG:
			begin = dtb_begin(addon_atmark_techno_thread_iotg_g3_intf1);
			size = dtb_size(addon_atmark_techno_thread_iotg_g3_intf1);
			break;
		case ADDON_BOARD_TYPE_X1:
			begin = dtb_begin(addon_atmark_techno_thread_x1_intf1);
			size = dtb_size(addon_atmark_techno_thread_x1_intf1);
			break;
		default:
			return -ENODEV;
		};
		break;
	case ADDON_INTERFACE2:
		switch (addon->type) {
		case ADDON_BOARD_TYPE_IOTG:
			begin = dtb_begin(addon_atmark_techno_thread_iotg_g3_intf2);
			size = dtb_size(addon_atmark_techno_thread_iotg_g3_intf2);
			break;
		default:
			return -ENODEV;
		};
		break;
	default:
		BUG();
	};
	armadillo_iotg_addon_dt_overlay(addon->dev, begin, size);

	return 0;
}
