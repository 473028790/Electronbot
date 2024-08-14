#ifndef __User_usb_H
#define __User_usb_H

#include "stdint.h"
#include "usb_device.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

struct UsbBuffer_t
{
	uint8_t extraDataTx[32];
	uint8_t rxData[2][43205]; // 43232bytes, 43200 of which are lcd buffer
	volatile uint16_t receivedPacketLen;
	volatile uint8_t pingPongIndex;
	volatile uint32_t rxDataOffset;
};
uint8_t* GetLcdBufferPtr();
void ReceiveUsbPacketUntilSizeIs(uint32_t _count);
void SwitchPingPongBuffer();
uint8_t* GetPingPongBufferPtr();
#endif
