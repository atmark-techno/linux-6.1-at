// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2024 Atmark Techno, Inc. All Rights Reserved.
 */

#ifndef __ASM_ARCH_ARMADILLO_X1L_EXTBOARD_H__
#define __ASM_ARCH_ARMADILLO_X1L_EXTBOARD_H__

struct extboard_device_descriptor {
	__be16	vendor_id;
	__be16	product_id;
	__be16	revision;
	__be32	serial_no;
	__u8	reserved[22];
	__u8	vendor_specific[96];
} __attribute__ ((packed));

#define NR_EXTBOARD_PINS	(60)
struct extboard_device {
	struct device *dev;
	struct extboard_device_descriptor desc;
	int gpios[NR_EXTBOARD_PINS];
};

/* EEPROM vendor ID */
#define EXTBOARD_VENDOR_ID_ATMARK_TECHNO	(0x0001)

/* EEPROM Atmark Techno product ID */
#define EXTBOARD_PRODUCT_ID_ATMARK_TECHNO_01		(0x0004)
#define EXTBOARD_PRODUCT_ID_ATMARK_TECHNO_01_ELS31	(0x0005)
#define EXTBOARD_PRODUCT_ID_ATMARK_TECHNO_01_WL1837	(0x0006)
#define EXTBOARD_PRODUCT_ID_ATMARK_TECHNO_01_NONE	(0x0007)

#define EXTBOARD_PRODUCT_ID_INVALID		(0xffff)

#define dtb_begin(f)	__dtb_##f##_begin
#define dtb_end(f)	__dtb_##f##_end
#define dtb_size(f)	(dtb_end(f) - dtb_begin(f))

#define extern_dtb(f)		\
extern uint8_t dtb_begin(f)[];	\
extern uint8_t dtb_end(f)[];

int armadillo_x1l_extboard_dt_overlay(struct device *dev, void *begin,
				      size_t size);

int extboard_setup_atmark_techno_01(struct extboard_device *edev);

#endif /* __ASM_ARCH_ARMADILLO_X1L_EXTBOARD_H__ */
