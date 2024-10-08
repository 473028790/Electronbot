#include "stmflash.h"

/**
 * @brief       从指定地址读取一个半字 (16位数据)
 * @param       faddr   : 读取地址 (此地址必须为2的倍数!!)
 * @retval      读取到的数据 (16位)
 */
uint16_t stmflash_read_halfword(uint32_t faddr)
{
    return *(volatile uint16_t *)faddr;
}

/**
 * @brief       从指定地址开始读出指定长度的数据
 * @param       raddr : 起始地址
 * @param       pbuf  : 数据指针
 * @param       length: 要读取的半字(16位)数,即2个字节的整数倍
 * @retval      无
 */
void stmflash_read(uint32_t raddr, uint16_t *pbuf, uint16_t length)
{
    uint16_t i;

    for (i = 0; i < length; i++)
    {
        pbuf[i] = stmflash_read_halfword(raddr);    /* 读取2个字节 */
        raddr += 2; /* 偏移2个字节 */
    }
}

/**
 * @brief       不检查的写入
                这个函数的假设已经把原来的扇区擦除过再写入
 * @param       waddr   : 起始地址 (此地址必须为2的倍数!!,否则写入出错!)
 * @param       pbuf    : 数据指针
 * @param       length  : 要写入的 半字(16位)数
 * @retval      无
 */
void stmflash_write_nocheck(uint32_t waddr, uint16_t *pbuf, uint16_t length)
{
    uint16_t i;
    for (i = 0; i < length; i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, waddr, pbuf[i]);
        waddr += 2; /* 指向下一个半字 */
    }
}

/**
 * @brief       在FLASH 指定位置, 写入指定长度的数据(自动擦除)
 *   @note      该函数往 STM32 内部 FLASH 指定位置写入指定长度的数据
 *              该函数会先检测要写入的扇区是否是空(全0XFFFF)的?, 如果
 *              不是, 则先擦除, 如果是, 则直接往扇区里面写入数据.
 *              数据长度不足扇区时，自动被回擦除前的数据
 * @param       waddr   : 起始地址 (此地址必须为2的倍数!!,否则写入出错!)
 * @param       pbuf    : 数据指针
 * @param       length  : 要写入的 半字(16位)数
 * @retval      无
 */
uint16_t g_flashbuf[STM32_SECTOR_SIZE / 2]; /* 最多是2K字节 */
void stmflash_write(uint32_t waddr, uint16_t *pbuf, uint16_t length)
{
    uint32_t secpos;    /* 扇区地址 */
    uint16_t secoff;    /* 扇区内偏移地址(16位字计算) */
    uint16_t secremain; /* 扇区内剩余地址(16位字计算) */
    uint16_t i;
    uint32_t offaddr;   /* 去掉0X08000000后的地址 */
    FLASH_EraseInitTypeDef flash_eraseop;
    uint32_t erase_addr;   /* 擦除错误，这个值为发生错误的扇区地址 */

    if (waddr < STM32_FLASH_BASE || (waddr >= (STM32_FLASH_BASE + STM32_FLASH_SIZE)))
    {
        return; /* 非法地址 */
    }

    HAL_FLASH_Unlock();                       /* FLASH解锁 */

    offaddr = waddr - STM32_FLASH_BASE;       /* 实际偏移地址. */
    secpos = offaddr / STM32_SECTOR_SIZE;       /* 扇区地址  0~127 for STM32F103RBT6 */
    secoff = (offaddr % STM32_SECTOR_SIZE) / 2; /* 在扇区内的偏移(2个字节为基本单位.) */
    secremain = STM32_SECTOR_SIZE / 2 - secoff; /* 扇区剩余空间大小 */
    if (length <= secremain)
    {
        secremain = length; /* 不大于该扇区范围 */
    }

    while (1)
    {
        stmflash_read(secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE, g_flashbuf, STM32_SECTOR_SIZE / 2); /* 读出整个扇区的内容 */
        for (i = 0; i < secremain; i++)                                                              /* 校验数据 */
        {
            if (g_flashbuf[secoff + i] != 0XFFFF)
            {
                break; /* 需要擦除 */
            }
        }
        if (i < secremain) /* 需要擦除 */
        { 
            flash_eraseop.TypeErase = FLASH_TYPEERASE_PAGES;        /* 选择面擦除 */
            flash_eraseop.NbPages = 1;
            flash_eraseop.PageAddress = secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE;  /* 要擦除的扇区 */
            HAL_FLASHEx_Erase( &flash_eraseop, &erase_addr);

            for (i = 0; i < secremain; i++)                               /* 复制 */
            {
                g_flashbuf[i + secoff] = pbuf[i];
            }
            stmflash_write_nocheck(secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE, g_flashbuf, STM32_SECTOR_SIZE / 2); /* 写入整个扇区 */
        }
        else
        {
            stmflash_write_nocheck(waddr, pbuf, secremain); /* 写已经擦除了的,直接写入扇区剩余区间. */
        }
        if (length == secremain)
        {
            break; /* 写入结束了 */
        }
        else       /* 写入未结束 */
        {
            secpos++;               /* 扇区地址增1 */
            secoff = 0;             /* 偏移位置为0 */
            pbuf += secremain;      /* 指针偏移 */
            waddr += secremain * 2; /* 写地址偏移(16位数据地址,需要*2) */
            length -= secremain;    /* 字节(16位)数递减 */
            if (length > (STM32_SECTOR_SIZE / 2))
            {
                secremain = STM32_SECTOR_SIZE / 2; /* 下一个扇区还是写不完 */
            }
            else
            {
                secremain = length; /* 下一个扇区可以写完了 */
            }
        }
    }

    HAL_FLASH_Lock(); /* 上锁 */
}

/******************************************************************************************/
/* 测试用代码 */

/**
 * @brief       测试写数据(写1个字)
 * @param       waddr : 起始地址
 * @param       wdata : 要写入的数据
 * @retval      读取到的数据
 */
void test_write(uint32_t waddr, uint16_t wdata)
{
    stmflash_write(waddr, &wdata, 1); /* 写入一个半字 */
}

// 用于将结构体写入Flash的函数
void write_board_config_to_flash(uint32_t waddr)
{
    // 检查写入地址是否为2字节对齐
    if (waddr % 2 != 0) {
        return;  // 地址必须是2字节对齐的，否则返回错误
    }

    // 临时缓冲区，用于存储结构体数据
    uint8_t buffer[BOARD_CONFIG_SIZE];
    
    // 将结构体数据拷贝到缓冲区中
    memcpy(buffer, &boardConfig, BOARD_CONFIG_SIZE);

    // Flash 写入要求按 16 位写入，因此我们需要将缓冲区按 2 字节为单位写入
    for (uint16_t i = 0; i < BOARD_CONFIG_SIZE; i += 2)
    {
        uint16_t data = buffer[i] | (buffer[i+1] << 8);  // 合成2个字节为1个16位数据
        stmflash_write(waddr + i, &data, 1);  // 写入1个16位数据
    }
}


// 用于从Flash读取结构体的函数
void read_board_config_from_flash(uint32_t raddr)
{
    // 临时缓冲区，用于存储读取到的数据
    uint8_t buffer[BOARD_CONFIG_SIZE];
    
    // Flash 读取按 16 位（2 字节）进行，所以我们需要分成多次读取
    for (uint16_t i = 0; i < BOARD_CONFIG_SIZE; i += 2)
    {
        uint16_t data = stmflash_read_halfword(raddr);  // 读取2个字节
        buffer[i] = data & 0xFF;           // 低8位存入缓冲区
        buffer[i + 1] = (data >> 8) & 0xFF; // 高8位存入缓冲区
        raddr += 2;  // 每次读取后，地址偏移2个字节
    }

    // 将读取的数据复制回boardConfig结构体
    memcpy(&boardConfig, buffer, BOARD_CONFIG_SIZE);
}