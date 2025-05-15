#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

// Includes
#include <LUFA/Drivers/USB/USB.h>
#include <avr/pgmspace.h>
#include "AppConfig.h"

// Tipos
typedef struct {
  USB_Descriptor_Configuration_Header_t    Config;
  USB_Descriptor_Interface_t               HID_Interface;
  USB_HID_Descriptor_HID_t                 HID_MouseHID;
  USB_Descriptor_Endpoint_t                HID_ReportINEndpoint;
} USB_Descriptor_Configuration_t;

// Protótipos
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, const void** const DescriptorAddress);

#endif