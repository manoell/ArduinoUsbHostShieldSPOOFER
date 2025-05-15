#ifndef _LUFA_CONFIG_H_
#define _LUFA_CONFIG_H_

// Configurações LUFA
#define USE_STATIC_OPTIONS               (USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)
#define USB_DEVICE_ONLY
#define FIXED_CONTROL_ENDPOINT_SIZE      8
#define FIXED_NUM_CONFIGURATIONS         1
#define USE_FLASH_DESCRIPTORS

// Tamanho máximo do endpoint
#define ENDPOINT_MAX_SIZE                64

// Endpoints máximos
#define MAX_ENDPOINT_INDEX               1

// USB Device Mode
#define NO_DEVICE_REMOTE_WAKEUP
#define NO_DEVICE_SELF_POWER
#define NO_INTERNAL_SERIAL

// Configurações HID
#define HID_HOST_BOOT_PROTOCOL_ONLY
#define HID_INCLUDE_DEVICE_APIS

#endif