// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2024 Atmark Techno, Inc. All Rights Reserved.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/of_gpio.h>

#include "armadillo_iotg_std_addon.h"

extern_dtb(addon_atmark_techno_en_ocean_iotg_g3_intf1);
extern_dtb(addon_atmark_techno_en_ocean_iotg_g3_intf2);
extern_dtb(addon_atmark_techno_en_ocean_x1_intf1);

#define PIN_RESET	(42)

#define BP35A3_RESET_ASSERT	(1)
#define BP35A3_RESET_DEASSERT	(0)

int addon_setup_atmark_techno_en_ocean(struct addon_device *adev)
{
	struct armadillo_iotg_addon *addon = to_addon(adev);
	void *begin;
	size_t size;
	int gpio_reset;

	switch (adev->intf) {
	case ADDON_INTERFACE1:
		switch (addon->type) {
		case ADDON_BOARD_TYPE_IOTG:
			begin = dtb_begin(addon_atmark_techno_en_ocean_iotg_g3_intf1);
			size = dtb_size(addon_atmark_techno_en_ocean_iotg_g3_intf1);
			break;
		case ADDON_BOARD_TYPE_X1:
			begin = dtb_begin(addon_atmark_techno_en_ocean_x1_intf1);
			size = dtb_size(addon_atmark_techno_en_ocean_x1_intf1);
			break;
		default:
			return -ENODEV;
		};
		break;
	case ADDON_INTERFACE2:
		switch (addon->type) {
		case ADDON_BOARD_TYPE_IOTG:
			begin = dtb_begin(addon_atmark_techno_en_ocean_iotg_g3_intf2);
			size = dtb_size(addon_atmark_techno_en_ocean_iotg_g3_intf2);
			break;
		default:
			return -ENODEV;
		};
		break;
	default:
		BUG();
	};
	armadillo_iotg_addon_dt_overlay(addon->dev, begin, size);

	gpio_reset = adev->gpios[PIN_RESET - 1];

	if (!gpio_is_valid(gpio_reset)) {
		dev_warn(addon->dev, "gpio_reset is invalid\n");
		return -EINVAL;
	}
	if (devm_gpio_request(addon->dev, gpio_reset, NULL)) {
		dev_warn(addon->dev, "gpio_reset request failed\n");
		return -EINVAL;
	}

	/* reset */
	gpio_direction_output(gpio_reset, BP35A3_RESET_ASSERT);
	mdelay(10); /* FIXME: reset period isn't specified in its data sheet. */
	gpio_direction_output(gpio_reset, BP35A3_RESET_DEASSERT);

	return 0;
}
