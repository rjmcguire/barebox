/*
 * Copyright (C) 2012 Antony Pavlov <antonynpavlov@gmail.com>
 *
 * This file is part of barebox.
 * See file CREDITS for list of people who contributed to this project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <common.h>
#include <types.h>
#include <driver.h>
#include <init.h>
#include <ns16550.h>
#include <io.h>
#include <asm/common.h>

#define JZ_UART_SHIFT	2

#define ier		(1 << JZ_UART_SHIFT)
#define fcr		(2 << JZ_UART_SHIFT)

static void jz_serial_reg_write(unsigned int val, unsigned long base,
	unsigned char reg_offset)
{
	switch (reg_offset) {
	case fcr:
		val |= 0x10; /* Enable uart module */
		break;
	case ier:
		val |= (val & 0x4) << 2;
		break;
	default:
		break;
	}

	writeb(val & 0xff, (void *)(base + reg_offset));
}

static struct NS16550_plat serial_plat = {
	.clock = 12000000,
	.shift = JZ_UART_SHIFT,
	.reg_write = &jz_serial_reg_write,
};

struct device_d *jz_add_uart(int id, unsigned long base)
{
	return add_ns16550_device(id, base, 8 << JZ_UART_SHIFT,
			IORESOURCE_MEM_8BIT, &serial_plat);
}