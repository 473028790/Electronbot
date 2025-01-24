#include "User_usb.h"

struct UsbBuffer_t usbBuffer;
void ReceiveUsbPacketUntilSizeIs(uint32_t _count)
{
    while (usbBuffer.receivedPacketLen != _count);
    usbBuffer.receivedPacketLen = 0;
}
int cnt21=0;
void SwitchPingPongBuffer()
{
		cnt21=1;
    usbBuffer.pingPongIndex = (usbBuffer.pingPongIndex == 0 ? 1 : 0);
    usbBuffer.rxDataOffset = 0;
}
int cnt55=0;
uint8_t* GetPingPongBufferPtr()
{
	cnt55++;
    return &(usbBuffer.rxData[usbBuffer.pingPongIndex][usbBuffer.rxDataOffset]);
}
uint8_t* GetLcdBufferPtr()
{
    return usbBuffer.rxData[usbBuffer.pingPongIndex == 0 ? 1 : 0];
}
uint8_t* GetExtraDataRxPtr()
{
    return GetLcdBufferPtr() + 60 * 240 * 3;
}
void SendUsbPacket(uint8_t* _data, uint32_t _len)
{
    uint8_t ret;
    do
    {
        ret = CDC_Transmit_HS(_data, _len);
    } while (ret != USBD_OK);
}
//int cnt22=0;
//static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t* Len)
//{
//	cnt22++;
//    // USBD_CDC_SetRxBuffer(&hUsbDeviceHS, frameBuffer[1]);
//    // USBD_CDC_ReceivePacket(&hUsbDeviceHS);
//    // Use LL version code instead

//    // Got data length
//    usbBuffer.receivedPacketLen = *Len;
//    if (usbBuffer.receivedPacketLen == 224)
//        SwitchPingPongBuffer();

//    // Prepare next receive
//    USBD_CDC_HandleTypeDef* hcdc = (USBD_CDC_HandleTypeDef*) (hUsbDeviceFS.pClassData);

//    // Set receive buffer
//    hcdc->RxBuffer = GetPingPongBufferPtr();
//    if (usbBuffer.receivedPacketLen == 512)
//    {
//        usbBuffer.rxDataOffset += 512;
//    }

//    return USBD_LL_PrepareReceive(&hUsbDeviceFS, CDC_OUT_EP, hcdc->RxBuffer, CDC_DATA_HS_OUT_PACKET_SIZE);

//}
