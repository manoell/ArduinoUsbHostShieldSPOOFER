#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

// Configurações do dispositivo
#define LOGITECH_VID              0x046D
#define G502_X_PLUS_PID           0xC095
#define G502_RELEASE_NUMBER       0x2700

// Mouse e teclado
#define MOUSE_EPADDR              (ENDPOINT_DIR_IN | 1)
#define MOUSE_EPSIZE              8
#define INTERFACE_ID_Mouse        0

// Strings USB
enum StringDescriptors_t {
  STRING_ID_Language         = 0,
  STRING_ID_Manufacturer     = 1,
  STRING_ID_Product          = 2,
  STRING_ID_Serial           = 3,
};

#endif