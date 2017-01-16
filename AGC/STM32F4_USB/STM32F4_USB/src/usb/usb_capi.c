/*
 * usb_capi.c
 *
 *  Created on: 2015年12月5日
 *      Author: kohill
 */

#include "usb_capi.h"

static uint8_t usb_com_Init(void *pdev , uint8_t cfgidx);
static uint8_t usb_com_DeInit(void *pdev , uint8_t cfgidx);
static uint8_t usb_com_Setup(void *pdev , USB_SETUP_REQ  *req);
static uint8_t usb_com_EO0_TxSent(void *pdev);
static uint8_t usb_com_EO0_RxReady(void *pdev);
static uint8_t usb_com_DataIn(void *pdev , uint8_t epnum);
static uint8_t usb_com_DataOut(void *pdev , uint8_t epnum);
static uint8_t usb_com_SOF(void *pdev);
static uint8_t* usb_com_GetCfgDeesc( uint8_t speed , uint16_t *length);
/* USB CDC device Configuration Descriptor */

#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define CDC_DATA_MAX_PACKET_SIZE       64   /* Endpoint IN & OUT Packet size */
#define CDC_CMD_PACKET_SZE             8    /* Control Endpoint Packet size */
#define CDC_IN_EP                       0x81  /* EP1 for data IN */
#define CDC_OUT_EP                      0x02  /* EP1 for data OUT */
#define CDC_CMD_EP                      0x82  /* EP2 for CDC commands */
#define USB_CDC_CONFIG_DESC_SIZ                (67)
#define USB_CDC_DESC_SIZ                       (67-9)

#define CDC_DESCRIPTOR_TYPE                     0x21

#define DEVICE_CLASS_CDC                        0x02
#define DEVICE_SUBCLASS_CDC                     0x00

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8))
#define MY_CONFIG_DESC
__ALIGN_BEGIN uint8_t usbd_cdc_CfgDesc[32] __ALIGN_END = {
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */
  32,                /* wTotalLength:no of returned bytes */
  0x00,
  0x01,   /* bNumInterfaces: 1 interface */
  0x01,   /* bConfigurationValue: Configuration value ,Used as a parameter to Set Configuration.*/
  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 100 mA */

  /*---------------------------------------------------------------------------*/

  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0xFF,   /* bInterfaceClass: Communication Interface Class */
  0xFF,   /* bInterfaceSubClass: Abstract Control Model */
  0xFF,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */

  //EndPoint discription
  0x07,//描述符长度
  USB_ENDPOINT_DESCRIPTOR_TYPE, //描述符类型：端点描述符
  0x81, //端点1，IN
  0x02, //Bulk
  LOBYTE(64),  //Max Packet Size
  HIBYTE(64),
  0x00, //BINterval, will be ignored for Bulk transfer.

  //EndPoint discription
  0x07,//描述符长度
  USB_ENDPOINT_DESCRIPTOR_TYPE, //描述符类型：端点描述符
  0x02, //端点2，Out
  0x02, //Bulk
  LOBYTE(64),  //Max Packet Size
  HIBYTE(64),
  0x00, //BINterval, will be ignored for Bulk transfer.

} ;

#include <stdbool.h>
static uint8_t databuf[64];
static bool isRxEd = false;
static uint8_t usb_com_Init(void *pdev , uint8_t cfgidx){

	/* Open EP IN */
	DCD_EP_Open(pdev,0x81, 64,USB_OTG_EP_BULK);

	/* Open EP OUT */
	DCD_EP_Open(pdev,0x02, 64,	USB_OTG_EP_BULK);

	/* Prepare Out endpoint to receive next packet */
	DCD_EP_PrepareRx(pdev,0x02, (uint8_t*) (databuf), 64);
	D_COUNT;
	return USBD_OK;
}
static uint8_t usb_com_DeInit(void *pdev , uint8_t cfgidx){
	D_COUNT;
	return USBD_OK;
}
static uint8_t usb_com_Setup(void *pdev , USB_SETUP_REQ  *req){
	D_COUNT;
	return USBD_OK;
}
static uint8_t usb_com_EO0_TxSent(void *pdev){
	D_COUNT;
	return USBD_OK;
}
static uint8_t usb_com_EO0_RxReady(void *pdev){
	D_COUNT;
	return USBD_OK;
}
static uint8_t usb_com_DataIn(void *pdev , uint8_t epnum){
	D_COUNT;
    /* Prepare the available data buffer to be sent on IN endpoint */
    DCD_EP_Tx (pdev,0x81,(uint8_t*)&databuf[0],64);
	return USBD_OK;
}
static uint8_t usb_com_DataOut(void *pdev , uint8_t epnum){
	D_COUNT;
	uint16_t USB_Rx_Cnt;

	/* Get the received data buffer and update the counter */
	USB_Rx_Cnt = ((USB_OTG_CORE_HANDLE*) pdev)->dev.out_ep[epnum].xfer_count;

	/* USB data will be immediately processed, this allow next USB traffic being
	 NAKed till the end of the application Xfer */

	/* Prepare Out endpoint to receive next packet */
	fwrite(databuf,64,1,stdout);
	DCD_EP_PrepareRx(pdev,	0x02, (uint8_t*) (databuf), 64);
	isRxEd = true;
	return USBD_OK;
}
static uint8_t usb_com_SOF(void *pdev){
	//每ms发送此包，无其他用处
	if(isRxEd)
		DCD_EP_Tx(pdev, CDC_IN_EP, (uint8_t*) &databuf[0],64);
	isRxEd = false;
	return USBD_OK;
}
static uint8_t* usb_com_GetCfgDeesc( uint8_t speed , uint16_t *length){
	  *length = sizeof (usbd_cdc_CfgDesc);
	  return usbd_cdc_CfgDesc;
}
USBD_Class_cb_TypeDef usb_com_cb = {
	usb_com_Init,
	usb_com_DeInit,
	usb_com_Setup,
	usb_com_EO0_TxSent,
	usb_com_EO0_RxReady,
	usb_com_DataIn,
	usb_com_DataOut,
	usb_com_SOF,
	0,
	0,
	usb_com_GetCfgDeesc,
};
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;
void usb_init(void){
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &usb_com_cb,&USR_cb);
}
