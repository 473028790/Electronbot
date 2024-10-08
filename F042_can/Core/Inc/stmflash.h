#ifndef __STMFLASH_H
#define __STMFLASH_H

#include "stm32f0xx_hal.h"
#include "configurations.h"
/* FLASH起始地址 */
#define STM32_FLASH_SIZE        0x8000         /* STM32 FLASH 总大小 */
#define STM32_FLASH_BASE        0x08000000      /* STM32 FLASH 起始地址 */

 /* STM32F103 扇区大小 */
#if STM32_FLASH_SIZE < 256 * 1024
#define STM32_SECTOR_SIZE   1024                /* 容量小于256K的 F103, 扇区大小为1K字节 */
#else
#define STM32_SECTOR_SIZE   2048                /* 容量大于等于于256K的 F103, 扇区大小为2K字节 */
#endif

/* FLASH解锁键值 */
#define STM32_FLASH_KEY1        0X45670123
#define STM32_FLASH_KEY2        0XCDEF89AB

#define FLASH_SAVE_ADDR 0X08006000 /* 设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小 + 0X08000000) */

/*SIZE表示半字长(2字节), 大小必须是2的整数倍, 如果不是的话, 强制对齐到2的整数倍 */
#define SIZE TEXT_LENTH / 2 + ((TEXT_LENTH % 2) ? 1 : 0)


/* 静态函数(仅限stmflash.c调用) */
static void stmflash_unlock(void);                  /* 解锁STM32 内部FLASH */
static void stmflash_lock(void);                    /* 锁定STM32 内部FLASH */
static uint8_t stmflash_get_error_status(void);     /* 获取FLASH错误状态 */
static uint8_t stmflash_wait_done(uint32_t time);   /* 等待操作完成 */
static uint8_t stmflash_erase_sector(uint32_t saddr);                   /* 擦除扇区 */
static uint8_t stmflash_write_halfword(uint32_t faddr, uint16_t data);  /* FLASH写半字 */

/* 接口函数(外部可调用) */
uint16_t stmflash_read_halfword(uint32_t faddr);                        /* FLASH读半字 */
void stmflash_read(uint32_t raddr, uint16_t *pbuf, uint16_t length);    /* 从指定地址开始读出指定长度的数据 */
void stmflash_write(uint32_t waddr, uint16_t *pbuf, uint16_t length);   /* 在FLASH 指定位置, 写入指定长度的数据(自动擦除) */

/* 测试函数 */
void test_write(uint32_t waddr, uint16_t wdata);
/* 结构体存储、读取函数 */
void write_board_config_to_flash(uint32_t waddr);
void read_board_config_from_flash(uint32_t raddr);
#endif


















