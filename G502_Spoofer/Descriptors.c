#include "Descriptors.h"

// Descritor do relatório HID
const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] = {
  HID_RI_USAGE_PAGE(8, 0x01),                    // Generic Desktop
  HID_RI_USAGE(8, 0x02),                         // Mouse
  HID_RI_COLLECTION(8, 0x01),                    // Application
    HID_RI_USAGE(8, 0x01),                       // Pointer
    HID_RI_COLLECTION(8, 0x00),                  // Physical
      // 5 botões para G502 X PLUS
      HID_RI_USAGE_PAGE(8, 0x09),                // Button
      HID_RI_USAGE_MINIMUM(8, 0x01),             // Button 1
      HID_RI_USAGE_MAXIMUM(8, 0x05),             // Button 5
      HID_RI_LOGICAL_MINIMUM(8, 0x00),
      HID_RI_LOGICAL_MAXIMUM(8, 0x01),
      HID_RI_REPORT_COUNT(8, 0x05),              // 5 botões
      HID_RI_REPORT_SIZE(8, 0x01),
      HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
      // 3 bits de padding
      HID_RI_REPORT_COUNT(8, 0x01),
      HID_RI_REPORT_SIZE(8, 0x03),
      HID_RI_INPUT(8, HID_IOF_CONSTANT),
      // X, Y, Wheel
      HID_RI_USAGE_PAGE(8, 0x01),                // Generic Desktop
      HID_RI_USAGE(8, 0x30),                     // X
      HID_RI_USAGE(8, 0x31),                     // Y
      HID_RI_USAGE(8, 0x38),                     // Wheel
      HID_RI_LOGICAL_MINIMUM(8, -127),
      HID_RI_LOGICAL_MAXIMUM(8, 127),
      HID_RI_REPORT_COUNT(8, 0x03),              // 3 eixos
      HID_RI_REPORT_SIZE(8, 0x08),
      HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),
    HID_RI_END_COLLECTION(0),
  HID_RI_END_COLLECTION(0)
};

// Descritor do dispositivo
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor = {
  .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
  
  .USBSpecification       = VERSION_BCD(2,0,0),
  .Class                  = USB_CSCP_NoDeviceClass,
  .SubClass               = USB_CSCP_NoDeviceSubclass,
  .Protocol               = USB_CSCP_NoDeviceProtocol,
  
  .Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
  
  .VendorID               = LOGITECH_VID,
  .ProductID              = G502_X_PLUS_PID,
  .ReleaseNumber          = G502_RELEASE_NUMBER,
  
  .ManufacturerStrIndex   = STRING_ID_Manufacturer,
  .ProductStrIndex        = STRING_ID_Product,
  .SerialNumStrIndex      = STRING_ID_Serial,
  
  .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

// Descritor de configuração
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor = {
  .Config = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},
    
    .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
    .TotalInterfaces        = 1,
    
    .ConfigurationNumber    = 1,
    .ConfigurationStrIndex  = NO_DESCRIPTOR,
    
    .ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),
    
    .MaxPowerConsumption    = USB_CONFIG_POWER_MA(500)
  },
  
  .HID_Interface = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
    
    .InterfaceNumber        = INTERFACE_ID_Mouse,
    .AlternateSetting       = 0x00,
    
    .TotalEndpoints         = 1,
    
    .Class                  = HID_CSCP_HIDClass,
    .SubClass               = HID_CSCP_BootSubclass,
    .Protocol               = HID_CSCP_MouseBootProtocol,
    
    .InterfaceStrIndex      = NO_DESCRIPTOR
  },
  
  .HID_MouseHID = {
    .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
    
    .HIDSpec                = VERSION_BCD(1,1,1),
    .CountryCode            = 0x00,
    .TotalReportDescriptors = 1,
    .HIDReportType          = HID_DTYPE_Report,
    .HIDReportLength        = sizeof(MouseReport)
  },
  
  .HID_ReportINEndpoint = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
    
    .EndpointAddress        = MOUSE_EPADDR,
    .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
    .EndpointSize           = MOUSE_EPSIZE,
    .PollingIntervalMS      = 0x05
  }
};

// Strings USB
const USB_Descriptor_String_t PROGMEM LanguageString = {
  .Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
  .UnicodeString          = {LANGUAGE_ID_ENG}
};

const USB_Descriptor_String_t PROGMEM ManufacturerString = {
  .Header                 = {.Size = USB_STRING_LEN(8), .Type = DTYPE_String},
  .UnicodeString          = L"Logitech"
};

const USB_Descriptor_String_t PROGMEM ProductString = {
  .Header                 = {.Size = USB_STRING_LEN(11), .Type = DTYPE_String},
  .UnicodeString          = L"G502 X PLUS"
};

const USB_Descriptor_String_t PROGMEM SerialNumberString = {
  .Header                 = {.Size = USB_STRING_LEN(8), .Type = DTYPE_String},
  .UnicodeString          = L"4ED7923A"
};

// Função para obter o descritor apropriado
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, const void** const DescriptorAddress) {
  const uint8_t  DescriptorType   = (wValue >> 8);
  const uint8_t  DescriptorNumber = (wValue & 0xFF);
  
  const void* Address = NULL;
  uint16_t    Size    = NO_DESCRIPTOR;
  
  switch (DescriptorType) {
    case DTYPE_Device:
      Address = &DeviceDescriptor;
      Size    = sizeof(USB_Descriptor_Device_t);
      break;
    case DTYPE_Configuration:
      Address = &ConfigurationDescriptor;
      Size    = sizeof(USB_Descriptor_Configuration_t);
      break;
    case DTYPE_String:
      switch (DescriptorNumber) {
        case STRING_ID_Language:
          Address = &LanguageString;
          Size    = pgm_read_byte(&LanguageString.Header.Size);
          break;
        case STRING_ID_Manufacturer:
          Address = &ManufacturerString;
          Size    = pgm_read_byte(&ManufacturerString.Header.Size);
          break;
        case STRING_ID_Product:
          Address = &ProductString;
          Size    = pgm_read_byte(&ProductString.Header.Size);
          break;
        case STRING_ID_Serial:
          Address = &SerialNumberString;
          Size    = pgm_read_byte(&SerialNumberString.Header.Size);
          break;
      }
      break;
    case HID_DTYPE_HID:
      Address = &ConfigurationDescriptor.HID_MouseHID;
      Size    = sizeof(USB_HID_Descriptor_HID_t);
      break;
    case HID_DTYPE_Report:
      Address = &MouseReport;
      Size    = sizeof(MouseReport);
      break;
  }
  
  *DescriptorAddress = Address;
  return Size;
}