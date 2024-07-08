/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2015 Renesas Electronics Corporation
 */

#ifndef __MYC_RZG2L_H
#define __MYC_RZG2L_H

#include <asm/arch/rmobile.h>

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_SPL
#define CONFIG_SPL_TARGET	"spl/u-boot-spl.scif"
#endif

/* boot option */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Generic Interrupt Controller Definitions */
/* RZ/G2L use GIC-v3 */
#define CONFIG_GICV3
#define GICD_BASE	0x11900000
#define GICR_BASE	0x11960000

/* console */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200, 38400 }

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

/* MEMORY */
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE

/* SDHI clock freq */
#define CONFIG_SH_SDHI_FREQ		133000000

#define DRAM_RSV_SIZE			0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(CONFIG_SYS_DDR4SIZE - DRAM_RSV_SIZE)
#define CONFIG_SYS_LOAD_ADDR		0x58000000
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR // Default load address for tfpt,bootp...
#define CONFIG_VERY_BIG_RAM
#define CONFIG_MAX_MEM_MAPPED		(CONFIG_SYS_DDR4SIZE - DRAM_RSV_SIZE)

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(1 * 1024 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)

/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		1048576

/* ENV setting */

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootm_size=0x10000000 \0" \
	"mmcdev=0 \0" \
	"bootpart=1 \0" \
	"rootpart=2 \0" \
	"prodmmcbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk${mmcdev}p${rootpart} \0" \
	"bootimage=booti 0x48080000 - 0x48000000 \0" \
	"loadaddr=0x48080000 \0" \
	"fdtaddr=0x48000000 \0" \
	"bootdelay=1 \0" \
	"script=boot.scr\0" \
	"image=Image\0" \
	"board_name=" CONFIG_SYS_BOARDNAME "\0" \
	"sdhi_sw=if test \"${board_name}\" = \"MYS-RZG2L\" ; then switch_sdhi1 wifi; fi \0" \
	"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"mmcload=fatload mmc ${mmcdev}:${bootpart} ${loadaddr} ${image};fatload mmc ${mmcdev}:${bootpart} ${fdtaddr} ${fdt_file};run prodmmcbootargs \0" \
        "bootselect=mmc dev 1;" \
		"if fatload mmc 1:${bootpart} ${loadaddr} ${script}; then " \
			"setenv mmcdev 1;" \
		"else " \
			"setenv mmcdev 0;" \
		"fi;\0" \
	"altbootcmd=run sdhi_sw; setenv mmcdev 0; run mmcload; run bootimage \0"


#define CONFIG_BOOTCOMMAND		"run sdhi_sw; run bootselect; run mmcload; run bootimage"

/* For board */
/* Ethernet RAVB */
#define CONFIG_BITBANGMII_MULTI

#endif /* __MYC_RZG2L_H */
