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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @file
 * @brief Resetting an JZ4740-based board
 */

#include <common.h>
#include <io.h>
#include <mach/jz4740_regs.h>

#define JZ_EXTAL 24000000

void __noreturn reset_cpu(ulong addr)
{
#if 0
	__raw_writew(WDT_TCSR_PRESCALE4 | WDT_TCSR_EXT_EN, (u16 *)WDT_TCSR);
	__raw_writew(0, (u16 *)WDT_TCNT);

	/* reset after 4ms */
	__raw_writew(JZ_EXTAL / 1000, (u16 *)WDT_TDR);
	/* enable wdt clock */
	__raw_writel(TCU_TSCR_WDTSC, (u32 *)TCU_TSCR);
	/* start wdt */
	__raw_writeb(WDT_TCER_TCEN, (u8 *)WDT_TCER);
#endif

	unreachable();
}
EXPORT_SYMBOL(reset_cpu);