#ifndef _USB_H_
#define _USB_H_

#include "UsbErrno.h"
#include "UsbList.h"

/*
 * USB-status codes:
 * USB_ST* maps to -E* and should go away in the future
 */
#define USB_ST_NOERROR          0
#define USB_ST_CRC              (-EILSEQ)
#define USB_ST_BITSTUFF         (-EPROTO)
#define USB_ST_NORESPONSE       (-ETIMEDOUT)                    /* device not responding/handshaking */
#define USB_ST_DATAOVERRUN      (-EOVERFLOW)
#define USB_ST_DATAUNDERRUN     (-EREMOTEIO)
#define USB_ST_BUFFEROVERRUN    (-ECOMM)
#define USB_ST_BUFFERUNDERRUN   (-ENOSR)
#define USB_ST_INTERNALERROR    (-EPROTO)                       /* unknown error */
#define USB_ST_SHORT_PACKET     (-EREMOTEIO)
#define USB_ST_PARTIAL_ERROR    (-EXDEV)                        /* ISO transfer only partially completed */
#define USB_ST_URB_KILLED       (-ENOENT)                       /* URB canceled by user */
#define USB_ST_URB_PENDING       (-EINPROGRESS)
#define USB_ST_REMOVED          (-ENODEV)                       /* device not existing or removed */
#define USB_ST_TIMEOUT          (-ETIMEDOUT)                    /* communication timed out, also in urb->status**/
#define USB_ST_NOTSUPPORTED     (-ENOSYS)                       
#define USB_ST_BANDWIDTH_ERROR  (-ENOSPC)                       /* too much bandwidth used */
#define USB_ST_URB_INVALID_ERROR  (-EINVAL)                     /* invalid value/transfer type */
#define USB_ST_URB_REQUEST_ERROR  (-ENXIO)                      /* invalid endpoint */
#define USB_ST_STALL            (-EPIPE)                        /* pipe stalled, also in urb->status*/

struct usb_devmap 
{
    UINT8 devicemap[16];
};


/*
 * declaring data structures presented before their definition met
 */
struct usb_device;
struct urb;

/* All standard descriptors have these 2 fields in common */
typedef struct usb_descriptor_header 
{
    __packed UINT8  bLength;
    __packed UINT8  bDescriptorType;
} USB_DESC_HDR_T;

/* Device descriptor */
typedef struct usb_device_descriptor 
{
    __packed UINT8  bLength;
    __packed UINT8  bDescriptorType;
    __packed UINT16 bcdUSB;
    __packed UINT8  bDeviceClass;
    __packed UINT8  bDeviceSubClass;
    __packed UINT8  bDeviceProtocol;
    __packed UINT8  bMaxPacketSize0;
    __packed UINT16 idVendor;
    __packed UINT16 idProduct;
    __packed UINT16 bcdDevice;
    __packed UINT8  iManufacturer;
    __packed UINT8  iProduct;
    __packed UINT8  iSerialNumber;
    __packed UINT8  bNumConfigurations;
} USB_DEV_DESC_T;

/* Endpoint descriptor */
typedef struct usb_endpoint_descriptor 
{
    __packed UINT8  bLength;
    __packed UINT8  bDescriptorType;
    __packed UINT8  bEndpointAddress;
    __packed UINT8  bmAttributes;
    __packed UINT16 wMaxPacketSize;
    __packed UINT8  bInterval;
    __packed UINT8  bRefresh;
    __packed UINT8  bSynchAddress;

    UINT8   *extra;                    /* Extra descriptors */
    INT     extralen;
} USB_EP_DESC_T;

/* Interface descriptor */
typedef struct usb_interface_descriptor 
{
    __packed UINT8  bLength;
    __packed UINT8  bDescriptorType;
    __packed UINT8  bInterfaceNumber;
    __packed UINT8  bAlternateSetting;
    __packed UINT8  bNumEndpoints;
    __packed UINT8  bInterfaceClass;
    __packed UINT8  bInterfaceSubClass;
    __packed UINT8  bInterfaceProtocol;
    __packed UINT8  iInterface;

    USB_EP_DESC_T *endpoint;

    UINT8  *extra;                     /* Extra descriptors */
    INT    extralen;
} USB_IF_DESC_T;

typedef struct usb_interface 
{
    USB_IF_DESC_T  *altsetting;
    INT   act_altsetting;              /* active alternate setting */
    INT   num_altsetting;              /* number of alternate settings */
    INT   max_altsetting;              /* total memory allocated */
    struct usb_driver  *driver;        /* driver */
    VOID  *private_data;
} USB_IF_T;

/* Configuration descriptor information.. */
typedef struct usb_config_descriptor 
{
    __packed UINT8   bLength;
    __packed UINT8   bDescriptorType;
    __packed UINT16  wTotalLength;
    __packed UINT8   bNumInterfaces;
    __packed UINT8   bConfigurationValue;
    __packed UINT8   iConfiguration;
    __packed UINT8   bmAttributes;
    __packed UINT8   MaxPower;

    USB_IF_T  *interface;
    UINT8   *extra;                    /* Extra descriptors */
    INT     extralen;
} USB_CONFIG_DESC_T;


/* String descriptor */
typedef struct usb_string_descriptor 
{
    __packed UINT8  bLength;
    __packed UINT8  bDescriptorType;
    __packed UINT16 wData[1];
} USB_STR_DESC_T;


/*
 * Device table entry for "new style" table-driven USB drivers.
 * User mode code can read these tables to choose which modules to load.
 * Declare the table as __devinitdata, and as a MODULE_DEVICE_TABLE.
 *
 * With a device table provide bind() instead of probe().  Then the
 * third bind() parameter will point to a matching entry from this
 * table.  (Null value reserved.)
 * 
 * Terminate the driver's table with an all-zeroes entry.
 * Init the fields you care about; zeroes are not used in comparisons.
 */
#define USB_DEVICE_ID_MATCH_VENDOR              0x0001
#define USB_DEVICE_ID_MATCH_PRODUCT             0x0002
#define USB_DEVICE_ID_MATCH_DEV_LO              0x0004
#define USB_DEVICE_ID_MATCH_DEV_HI              0x0008
#define USB_DEVICE_ID_MATCH_DEV_CLASS           0x0010
#define USB_DEVICE_ID_MATCH_DEV_SUBCLASS        0x0020
#define USB_DEVICE_ID_MATCH_DEV_PROTOCOL        0x0040
#define USB_DEVICE_ID_MATCH_INT_CLASS           0x0080
#define USB_DEVICE_ID_MATCH_INT_SUBCLASS        0x0100
#define USB_DEVICE_ID_MATCH_INT_PROTOCOL        0x0200

#define USB_DEVICE_ID_MATCH_DEVICE              (USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT)
#define USB_DEVICE_ID_MATCH_DEV_RANGE           (USB_DEVICE_ID_MATCH_DEV_LO | USB_DEVICE_ID_MATCH_DEV_HI)
#define USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION  (USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_RANGE)
#define USB_DEVICE_ID_MATCH_DEV_INFO \
        (USB_DEVICE_ID_MATCH_DEV_CLASS | USB_DEVICE_ID_MATCH_DEV_SUBCLASS | USB_DEVICE_ID_MATCH_DEV_PROTOCOL)
#define USB_DEVICE_ID_MATCH_INT_INFO \
        (USB_DEVICE_ID_MATCH_INT_CLASS | USB_DEVICE_ID_MATCH_INT_SUBCLASS | USB_DEVICE_ID_MATCH_INT_PROTOCOL)

/* Some useful macros */
#define USB_DEVICE(vend,prod) \
        { USB_DEVICE_ID_MATCH_DEVICE, vend, prod, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

#define USB_DEVICE_VER(vend,prod,lo,hi) \
        { USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION, vend, prod, lo, hi, 0, 0, 0, 0, 0, 0, 0 }

#define USB_DEVICE_INFO(cl,sc,pr) \
        { USB_DEVICE_ID_MATCH_DEV_INFO, 0, 0, 0, 0, cl, sc, pr, 0, 0, 0, 0 }

#define USB_INTERFACE_INFO(cl,sc,pr) \
        { USB_DEVICE_ID_MATCH_INT_INFO, 0, 0, 0, 0, 0, 0, 0, cl, sc, pr, 0 }

typedef struct usb_device_id 
{
    /* This bitmask is used to determine which of the following fields
     * are to be used for matching.
     */
    UINT16  match_flags;

    /*
     * vendor/product codes are checked, if vendor is nonzero
     * Range is for device revision (bcdDevice), inclusive;
     * zero values here mean range isn't considered
     */
    UINT16  idVendor;
    UINT16  idProduct;
    UINT16  bcdDevice_lo; 
    UINT16	bcdDevice_hi;

    /*
     * if device class != 0, these can be match criteria;
     * but only if this bDeviceClass value is nonzero
     */
    UINT8   bDeviceClass;
    UINT8   bDeviceSubClass;
    UINT8   bDeviceProtocol;

    /*
     * if interface class != 0, these can be match criteria;
     * but only if this bInterfaceClass value is nonzero
     */
    UINT8   bInterfaceClass;
    UINT8   bInterfaceSubClass;
    UINT8   bInterfaceProtocol;

    /*
     * for driver's use; not involved in driver matching.
     */
    UINT32  driver_info;
} USB_DEV_ID_T;

typedef struct usb_driver 
{
    const CHAR  *name;

    VOID  *(*probe)(struct usb_device *dev, UINT32 intf, const USB_DEV_ID_T *id);
    VOID  (*disconnect)(struct usb_device *, VOID *);
    USB_LIST_T  driver_list;
#ifdef _NUCLEUS_
    NU_SEMAPHORE serialize;
#endif    
    /* ioctl -- userspace apps can talk to drivers through usbdevfs */
    INT  (*ioctl)(struct usb_device *dev, UINT32 code, VOID *buf);
    /* 
     * support for "new-style" USB hotplugging
     * binding policy can be driven from user mode too
     */
    const USB_DEV_ID_T  *id_table;
    /* suspend before the bus suspends;
     * disconnect or resume when the bus resumes */
    VOID (*suspend)(struct usb_device *dev);
    VOID (*resume)(struct usb_device *dev);
} USB_DRIVER_T;
       
       
        
/*----------------------------------------------------------------------------* 
 * New USB Structures                                                         *
 *----------------------------------------------------------------------------*/
/*
 * urb->transfer_flags:
 */
#define USB_DISABLE_SPD         0x0001
#define USB_ISO_ASAP            0x0002
#define USB_ASYNC_UNLINK        0x0008
#define USB_QUEUE_BULK          0x0010
#define USB_NO_FSBR             0x0020
#define USB_TIMEOUT_KILLED      0x1000 /* only set by HCD! */

typedef struct
{
    UINT32  offset;
    UINT32  length;                    /* expected length */
    UINT32  actual_length;
    UINT32  status;
} ISO_PACKET_DESCRIPTOR_T, *PISO_PACKET_DESCRIPTOR_T;

typedef struct urb
{
    VOID    *hcpriv;                   /* private data for host controller */
    USB_LIST_T  urb_list;              /* list pointer to all active urbs */
    struct urb  *next;                 /* pointer to next URB  */
    struct usb_device  *dev;           /* pointer to associated USB device */
    UINT32  pipe;                      /* pipe information */
    INT     status;                    /* returned status */
    UINT32  transfer_flags;            /* USB_DISABLE_SPD | USB_ISO_ASAP | etc. */
    VOID    *transfer_buffer;          /* associated data buffer */
    INT     transfer_buffer_length;    /* data buffer length */
    INT     actual_length;             /* actual data buffer length */
    INT     bandwidth;                 /* bandwidth for this transfer request (INT or ISO) */
    UINT8   *setup_packet;             /* setup packet (control only) */

    INT     start_frame;               /* start frame (iso/irq only) */
    INT     number_of_packets;         /* number of packets in this request (iso) */
    INT     interval;                  /* polling interval (irq only) */
    INT     error_count;               /* number of errors in this transfer (iso only) */
    INT     timeout;                   /* timeout (in jiffies) */
    VOID    *context;
#ifdef _NUCLEUS_
    NU_TASK *task;
    NU_EVENT_GROUP events;
#endif    
    VOID (*complete)(struct urb *);
    ISO_PACKET_DESCRIPTOR_T  *iso_frame_desc;
} URB_T, *PURB_T;


#define FILL_CONTROL_URB(a,aa,b,c,d,e,f,g) \
    do {\
        (a)->dev=aa;\
        (a)->pipe=b;\
        (a)->setup_packet=c;\
        (a)->transfer_buffer=d;\
        (a)->transfer_buffer_length=e;\
        (a)->complete=f;\
        (a)->context=g;\
    } while (0)


#define FILL_BULK_URB(a,aa,b,c,d,e,f) \
    do {\
        (a)->dev=aa;\
        (a)->pipe=b;\
        (a)->transfer_buffer=c;\
        (a)->transfer_buffer_length=d;\
        (a)->complete=e;\
        (a)->context=f;\
    } while (0)

    
#define FILL_INT_URB(a,aa,b,c,d,e,f,g) \
    do {\
        (a)->dev=aa;\
        (a)->pipe=b;\
        (a)->transfer_buffer=c;\
        (a)->transfer_buffer_length=d;\
        (a)->complete=e;\
        (a)->context=f;\
        (a)->interval=g;\
        (a)->start_frame=-1;\
    } while (0)


#define FILL_CONTROL_URB_TO(a,aa,b,c,d,e,f,g,h) \
    do {\
        (a)->dev=aa;\
        (a)->pipe=b;\
        (a)->setup_packet=c;\
        (a)->transfer_buffer=d;\
        (a)->transfer_buffer_length=e;\
        (a)->complete=f;\
        (a)->context=g;\
        (a)->timeout=h;\
    } while (0)


#define FILL_BULK_URB_TO(a,aa,b,c,d,e,f,g) \
    do {\
        (a)->dev=aa;\
        (a)->pipe=b;\
        (a)->transfer_buffer=c;\
        (a)->transfer_buffer_length=d;\
        (a)->complete=e;\
        (a)->context=f;\
        (a)->timeout=g;\
    } while (0)

    


/* -------------------------------------------------------------------------- */

typedef struct usb_operations 
{
    INT (*allocate)(struct usb_device *);
    INT (*deallocate)(struct usb_device *);
    INT (*get_frame_number) (struct usb_device *usb_dev);
    INT (*submit_urb)(PURB_T purb);
    INT (*unlink_urb)(PURB_T purb);
} USB_OP_T;

/*
 * Allocated per bus we have
 */
typedef struct usb_bus 
{
    INT    busnum;                     /* Bus number (in order of reg) */
    struct usb_devmap  devmap;         /* Device map */
    USB_OP_T  *op;        			   /* Operations (specific to the HC) */
    struct usb_device  *root_hub;      /* Root hub */
    USB_LIST_T  bus_list;
    VOID   *hcpriv;                    /* Host Controller private data */

    INT bandwidth_allocated;           /* on this Host Controller; */
                                       /* applies to Int. and Isoc. pipes; */
                                       /* measured in microseconds/frame; */
                                       /* range is 0..900, where 900 = */
                                       /* 90% of a 1-millisecond frame */
    INT    bandwidth_int_reqs;         /* number of Interrupt requesters */
    INT    bandwidth_isoc_reqs;        /* number of Isoc. requesters */
} USB_BUS_T;

#define USB_MAXCHILDREN         (16)   /* This is arbitrary */

typedef struct usb_device 
{
    INT     devnum;                    	/* Device number on USB bus */
    INT     slow;                      	/* Slow device? */
    INT     refcnt;                    	/* atomic_t, Reference count */

    UINT32  toggle[2];                 	/* one bit for each endpoint ([0] = IN, [1] = OUT) */
    UINT32  halted[2];                 	/* endpoint halts; one bit per endpoint # & direction; */
                                       	/* [0] = IN, [1] = OUT */
    INT     epmaxpacketin[16];         	/* INput endpoint specific maximums */
    INT     epmaxpacketout[16];        	/* OUTput endpoint specific maximums */

    struct usb_device  *parent;
    USB_BUS_T  *bus;                   	/* Bus we're part of */

    USB_DEV_DESC_T  descriptor;			/* Descriptor */
    USB_CONFIG_DESC_T *config;   		/* All of the configs */
    USB_CONFIG_DESC_T *actconfig;		/* the active configuration */

    CHAR    **rawdescriptors;          	/* Raw descriptors for each config */
  
    INT     have_langid;               	/* whether string_langid is valid yet */
    INT     string_langid;             	/* language ID for strings */
  
    VOID    *hcpriv;                   	/* Host Controller private data */
        
    /*
     * Child devices - these can be either new devices
     * (if this is a hub device), or different instances
     * of this same device.
     *
     * Each instance needs its own set of data structures.
     */

    INT     maxchild;                  /* Number of ports if hub */
    struct usb_device  *children[USB_MAXCHILDREN];
} USB_DEV_T;


/*
 * Calling this entity a "pipe" is glorifying it. A USB pipe
 * is something embarrassingly simple: it basically consists
 * of the following information:
 *  - device number (7 bits)
 *  - endpoint number (4 bits)
 *  - current Data0/1 state (1 bit)
 *  - direction (1 bit)
 *  - speed (1 bit)
 *  - max packet size (2 bits: 8, 16, 32 or 64) [Historical; now gone.]
 *  - pipe type (2 bits: control, interrupt, bulk, isochronous)
 *
 * That's 18 bits. Really. Nothing more. And the USB people have
 * documented these eighteen bits as some kind of glorious
 * virtual data structure.
 *
 * Let's not fall in that trap. We'll just encode it as a simple
 * UINT32. The encoding is:
 *
 *  - max size:         bits 0-1        (00 = 8, 01 = 16, 10 = 32, 11 = 64) [Historical; now gone.]
 *  - direction:        bit 7           (0 = Host-to-Device [Out], 1 = Device-to-Host [In])
 *  - device:           bits 8-14
 *  - endpoint:         bits 15-18
 *  - Data0/1:          bit 19
 *  - speed:            bit 26          (0 = Full, 1 = Low Speed)
 *  - pipe type:        bits 30-31      (00 = isochronous, 01 = interrupt, 10 = control, 11 = bulk)
 *
 * Why? Because it's arbitrary, and whatever encoding we select is really
 * up to us. This one happens to share a lot of bit positions with the UHCI
 * specification, so that much of the uhci driver can just mask the bits
 * appropriately.
 */

#define PIPE_ISOCHRONOUS                0
#define PIPE_INTERRUPT                  1
#define PIPE_CONTROL                    2
#define PIPE_BULK                       3

#define usb_maxpacket(dev, pipe, out)   (out \
                                ? (dev)->epmaxpacketout[usb_pipeendpoint(pipe)] \
                                : (dev)->epmaxpacketin [usb_pipeendpoint(pipe)] )
#define usb_packetid(pipe)      (((pipe) & USB_DIR_IN) ? USB_PID_IN : USB_PID_OUT)

#define usb_pipeout(pipe)       ((((pipe) >> 7) & 1) ^ 1)
#define usb_pipein(pipe)        (((pipe) >> 7) & 1)
#define usb_pipedevice(pipe)    (((pipe) >> 8) & 0x7f)
#define usb_pipe_endpdev(pipe)  (((pipe) >> 8) & 0x7ff)
#define usb_pipeendpoint(pipe)  (((pipe) >> 15) & 0xf)
#define usb_pipedata(pipe)      (((pipe) >> 19) & 1)
#define usb_pipeslow(pipe)      (((pipe) >> 26) & 1)
#define usb_pipetype(pipe)      (((pipe) >> 30) & 3)
#define usb_pipeisoc(pipe)      (usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
#define usb_pipeint(pipe)       (usb_pipetype((pipe)) == PIPE_INTERRUPT)
#define usb_pipecontrol(pipe)   (usb_pipetype((pipe)) == PIPE_CONTROL)
#define usb_pipebulk(pipe)      (usb_pipetype((pipe)) == PIPE_BULK)

#define PIPE_DEVEP_MASK         0x0007ff00

/* The D0/D1 toggle bits */
#define usb_gettoggle(dev, ep, out) (((dev)->toggle[out] >> ep) & 1)
#define usb_dotoggle(dev, ep, out)  ((dev)->toggle[out] ^= (1 << ep))
#define usb_settoggle(dev, ep, out, bit) ((dev)->toggle[out] = ((dev)->toggle[out] & ~(1 << ep)) | ((bit) << ep))

/* Endpoint halt control/status */
#define usb_endpoint_out(ep_dir)        (((ep_dir >> 7) & 1) ^ 1)
#define usb_endpoint_halt(dev, ep, out) ((dev)->halted[out] |= (1 << (ep)))
#define usb_endpoint_running(dev, ep, out) ((dev)->halted[out] &= ~(1 << (ep)))
#define usb_endpoint_halted(dev, ep, out) ((dev)->halted[out] & (1 << (ep)))

static __inline UINT32 __create_pipe(USB_DEV_T *dev, UINT32 endpoint)
{
        return (dev->devnum << 8) | (endpoint << 15) | (dev->slow << 26);
}

static __inline UINT32 __default_pipe(USB_DEV_T *dev)
{
        return (dev->slow << 26);
}

/* Create various pipes... */
#define usb_sndctrlpipe(dev,endpoint)   (0x80000000 | __create_pipe(dev,endpoint))
#define usb_rcvctrlpipe(dev,endpoint)   (0x80000000 | __create_pipe(dev,endpoint) | USB_DIR_IN)
#define usb_sndisocpipe(dev,endpoint)   (0x00000000 | __create_pipe(dev,endpoint))
#define usb_rcvisocpipe(dev,endpoint)   (0x00000000 | __create_pipe(dev,endpoint) | USB_DIR_IN)
#define usb_sndbulkpipe(dev,endpoint)   (0xC0000000 | __create_pipe(dev,endpoint))
#define usb_rcvbulkpipe(dev,endpoint)   (0xC0000000 | __create_pipe(dev,endpoint) | USB_DIR_IN)
#define usb_sndintpipe(dev,endpoint)    (0x40000000 | __create_pipe(dev,endpoint))
#define usb_rcvintpipe(dev,endpoint)    (0x40000000 | __create_pipe(dev,endpoint) | USB_DIR_IN)
#define usb_snddefctrl(dev)             (0x80000000 | __default_pipe(dev))
#define usb_rcvdefctrl(dev)             (0x80000000 | __default_pipe(dev) | USB_DIR_IN)

extern USB_LIST_T  usb_driver_list;
extern USB_LIST_T  usb_bus_list;


/*-------------------------------------------------------------------------
 *   Exported Functions
 *-------------------------------------------------------------------------*/
/* USB System */
extern INT  InitUsbSystem(VOID);
extern INT  UsbInitializeOHCI(INT irq, VOID *mem_base);
extern VOID Hub_CheckIrqEvent(VOID);

/* USB Device Driver */
extern INT  USB_RegisterDriver(USB_DRIVER_T *);
extern VOID USB_DeregisterDriver(USB_DRIVER_T *);
extern VOID USB_ScanDevices(VOID);
extern VOID USB_DriverClaimInterface(USB_DRIVER_T *driver, USB_IF_T *iface, VOID* priv);
extern INT  USB_InterfaceClaimed(USB_IF_T *iface);
extern VOID USB_DriverReleaseInterface(USB_DRIVER_T *driver, USB_IF_T *iface);
extern const  USB_DEV_ID_T *usb_match_id(USB_DEV_T *dev, USB_IF_T *interface,
       				const USB_DEV_ID_T *id);

/* USB Device */
extern USB_DEV_T  *USB_AllocateDevice(USB_DEV_T *parent, USB_BUS_T *);
extern VOID USB_FreeDevice(USB_DEV_T *);
extern VOID USB_ConnectDevice(USB_DEV_T *dev);
extern VOID USB_DisconnectDevice(USB_DEV_T **);
extern INT  USB_SettleNewDevice(USB_DEV_T *dev);
extern INT  USB_ResetDevice(USB_DEV_T *dev);
extern VOID USB_IncreaseDeviceUser(USB_DEV_T *);
#define USB_DecreaseDeviceUser  USB_FreeDevice

/* Bandwidth */
extern INT  USB_CheckBandwidth(USB_DEV_T *dev, URB_T *urb);
extern VOID USB_ClaimBandwidth(USB_DEV_T *dev, URB_T *urb, INT bustime, INT isoc);
extern VOID USB_ReleaseBandwidth(USB_DEV_T *dev, URB_T *urb, INT isoc);

/* USB Hub */
extern INT  USB_InitHubDriver(VOID);
extern VOID USB_RemoveHubDriver(VOID);
extern INT  USB_RootHubString(INT id, INT serial, CHAR *type, UINT8 *data, INT len);

/* URB */
extern URB_T  *USB_AllocateUrb(INT iso_packets);
extern VOID USB_FreeUrb(URB_T *urb);
extern INT  USB_SubmitUrb(URB_T *urb);
extern INT  USB_UnlinkUrb(URB_T *urb);

/* Blocking Mode Transfer */
extern INT  USB_SendControlMessage(USB_DEV_T *dev, UINT32 pipe, UINT8 request, UINT8 requesttype, UINT16 value, UINT16 index, VOID *data, UINT16 size, INT timeout);
extern INT  USB_SendBulkMessage(USB_DEV_T *usb_dev, UINT32 pipe, VOID *data, INT len, INT *actual_length, INT timeout);

/* Standard Device Request Commands */
extern INT  USB_GetDescriptor(USB_DEV_T *dev, UINT8 desctype,
           		UINT8 descindex, VOID *buf, INT size);
extern INT  USB_GetClassDescriptor(USB_DEV_T *dev, INT ifnum, UINT8 desctype,
           		UINT8 descindex, VOID *buf, INT size);
extern INT  USB_GetDeviceDescriptor(USB_DEV_T *dev);
extern INT  USB_GetExtraDescriptor(CHAR *buffer, UINT32 size, UINT8 type, VOID **ptr);
extern INT  USB_GetStringDescriptor(USB_DEV_T *dev, UINT16 langid, UINT8 index, VOID *buf, INT size);
extern INT  USB_SetAddress(USB_DEV_T *dev);
extern INT  USB_SetInterface(USB_DEV_T *dev, INT ifnum, INT alternate);
extern INT  USB_GetConfiguration(USB_DEV_T *dev);
extern INT  USB_SetConfiguration(USB_DEV_T *dev, INT configuration);
extern INT  USB_GetStatus(USB_DEV_T *dev, INT type, INT target, VOID *data);

/* HID Class Request Commands */
extern INT	USB_GetProtocol(USB_DEV_T *dev, INT ifnum);
extern INT	USB_SetProtocol(USB_DEV_T *dev, INT ifnum, INT protocol);
extern INT	USB_GetReport(USB_DEV_T *dev, INT ifnum, UINT8 type,
           			UINT8 id, VOID *buf, INT size);
extern INT  USB_SetReport(USB_DEV_T *dev, INT ifnum, UINT8 type,
       				UINT8 id, VOID *buf, INT size);
extern INT  USB_SetIdle(USB_DEV_T *dev, INT ifnum, INT duration, INT report_id);

/* Miscellaneous */
extern INT  USB_GetCurrentFrameNumber(USB_DEV_T *usb_dev);
extern VOID USB_DestroyConfiguration(USB_DEV_T *dev);
extern USB_IF_T	 *USB_GetInterfaceData(USB_DEV_T *dev, INT ifnum);
extern USB_EP_DESC_T  *USB_GetEndpointDescriptor(USB_DEV_T *dev, INT epnum);
extern INT	USB_ClearHalt(USB_DEV_T *dev, INT pipe);
extern VOID	USB_SetMaximumPacketSize(USB_DEV_T *dev);
extern INT	USB_TranslateString(USB_DEV_T *dev, INT index, CHAR *buf, INT size);

#endif  /* _USB_H_ */
