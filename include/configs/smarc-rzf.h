// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2022, Renesas Electronics Corporation. All rights reserved.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef CONFIG_SPL
#ifdef CONFIG_SPL_NOR_SUPPORT
#define CONFIG_SYS_UBOOT_BASE       0x20020000
#endif

#ifdef CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME		"u-boot.itb"
#endif

#ifdef CONFIG_SPL_BUILD
/* use CONFIG_XIP configuration for Elimination of atomic instructions */
#define CONFIG_XIP  1
#endif /* CONFIG_SPL_BUILD */

#endif /*CONFIG_SPL */

/*
 * CPU and Board Configuration Options
 */

/*
 * Cache Configuration
 */
#define CONFIG_SYS_CACHELINE_SIZE	64


/* boot option */
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

#define DRAM_RSV_SIZE			0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(CONFIG_RZF_DDR_SIZE - DRAM_RSV_SIZE)
#define CONFIG_MAX_MEM_MAPPED		(CONFIG_RZF_DDR_SIZE - DRAM_RSV_SIZE)
#define CONFIG_VERY_BIG_RAM

/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		3145728

/* ENV setting */
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"fdt_addr_r=0x48000000\0" \
	"fdtfile=r9a07g043f01-smarc.dtb\0" \
	"kernel_addr_r=0x48080000\0" \
	"boot_efi_binary=efi/boot/"BOOTEFI_NAME"\0" \
	"boot_mmc=" \
			"if test -e mmc ${mmcdev}:1 ${boot_efi_binary}; then " \
				"load mmc ${mmcdev}:1 " \
				"${kernel_addr_r} ${boot_efi_binary};" \
				"bootefi ${kernel_addr_r};" \
			"elif test -e mmc ${mmcdev}:2 ${boot_efi_binary}; then " \
				"load mmc ${mmcdev}:2 " \
				"${kernel_addr_r} ${boot_efi_binary};" \
				"bootefi ${kernel_addr_r};" \
			"fi;\0" \
	"load_mmc=" \
			"setenv mmcdev 0;" \
			"run boot_mmc;" \
			"setenv mmcdev 1;" \
			"run boot_mmc; \0" \
	"distro_bootcmd=" \
			"run load_mmc;\0" \
	"bootcmd=run distro_bootcmd\0" \

#ifndef CONFIG_SPL_BUILD
#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 1) \
	func(MMC, mmc, 0) \
	func(PXE, pxe, na) \
	func(DHCP, dhcp, na)
#include <config_distro_bootcmd.h>
#endif

/* For board */
/* Ethernet RAVB */
#define CONFIG_BITBANGMII_MULTI

#endif /* __CONFIG_H */
