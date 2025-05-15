// Incluir cabeçalhos
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

// Incluir LUFA
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Peripheral/Serial.h>
#include "Descriptors.h"

// Estado do mouse
static uint8_t MouseButtons = 0;
static int8_t MouseX = 0;
static int8_t MouseY = 0;
static int8_t MouseWheel = 0;

// Buffer de comando
static char CommandBuffer[64];
static uint8_t CommandIndex = 0;

// Interface HID de mouse
USB_ClassInfo_HID_Device_t Mouse_HID_Interface = {
  .Config = {
    .InterfaceNumber = INTERFACE_ID_Mouse,
    .ReportINEndpoint = {
      .Address = MOUSE_EPADDR,
      .Size = MOUSE_EPSIZE,
      .Banks = 1,
    },
    .PrevReportINBuffer = NULL,
    .PrevReportINBufferSize = 0,
  }
};

// Inicialização de serial
void SetupSerial(void) {
  // Configurar USART1 para 115200 8N1
  Serial_Init(115200, false);
  
  // Limpar buffer de comando
  memset(CommandBuffer, 0, sizeof(CommandBuffer));
  CommandIndex = 0;
}

// Enviar mensagem via serial
void SendSerialString(const char* string) {
  Serial_TxString(string);
  Serial_TxByte('\r');
  Serial_TxByte('\n');
}

// Processar caráter serial
void ProcessSerialChar(char c) {
  // Se é um caractere de retorno ou nova linha, processar comando
  if (c == '\r' || c == '\n') {
    if (CommandIndex > 0) {
      CommandBuffer[CommandIndex] = '\0';
      ProcessCommand(CommandBuffer);
      CommandIndex = 0;
    }
  }
  // Caso contrário, adicionar ao buffer
  else if (CommandIndex < sizeof(CommandBuffer) - 1) {
    CommandBuffer[CommandIndex++] = c;
  }
}

// Mover mouse em passos
void MoveMouseInSteps(int dx, int dy) {
  // Movimento X
  while (dx != 0) {
    if (dx > 127) {
      MouseX = 127;
      dx -= 127;
    } 
    else if (dx < -127) {
      MouseX = -127;
      dx += 127;
    } 
    else {
      MouseX = dx;
      dx = 0;
    }
    
    // Enviar relatório
    HID_Device_USBTask(&Mouse_HID_Interface);
    MouseX = 0;
  }
  
  // Movimento Y
  while (dy != 0) {
    if (dy > 127) {
      MouseY = 127;
      dy -= 127;
    } 
    else if (dy < -127) {
      MouseY = -127;
      dy += 127;
    } 
    else {
      MouseY = dy;
      dy = 0;
    }
    
    // Enviar relatório
    HID_Device_USBTask(&Mouse_HID_Interface);
    MouseY = 0;
  }
}

// Processar comando
void ProcessCommand(char* cmd) {
  // Comandos da forma "syl3nt123:456"
  if (strncmp(cmd, "syl3nt", 6) == 0) {
    int dx = 0, dy = 0;
    char* sep = strchr(cmd + 6, ':');
    
    if (sep) {
      *sep = '\0';
      dx = atoi(cmd + 6);
      dy = atoi(sep + 1);
      
      // Mover para posição
      MoveMouseInSteps(dx, dy);
      
      // Clicar
      MouseButtons |= (1 << 0);
      HID_Device_USBTask(&Mouse_HID_Interface);
      
      // Soltar
      MouseButtons &= ~(1 << 0);
      HID_Device_USBTask(&Mouse_HID_Interface);
      
      // Voltar para posição original
      MoveMouseInSteps(-dx, -dy);
      
      SendSerialString("syl3nt executado");
    }
  }
  // Comandos da forma "movsht123:456"
  else if (strncmp(cmd, "movsht", 6) == 0) {
    int dx = 0, dy = 0;
    char* sep = strchr(cmd + 6, ':');
    
    if (sep) {
      *sep = '\0';
      dx = atoi(cmd + 6);
      dy = atoi(sep + 1);
      
      // Mover para posição
      MoveMouseInSteps(dx, dy);
      
      // Clicar
      MouseButtons |= (1 << 0);
      HID_Device_USBTask(&Mouse_HID_Interface);
      
      // Soltar
      MouseButtons &= ~(1 << 0);
      HID_Device_USBTask(&Mouse_HID_Interface);
      
      SendSerialString("movsht executado");
    }
  }
}

// Função principal
int main(void) {
  // Desabilitar watchdog
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  
  // Desabilitar clock prescaling
  clock_prescale_set(clock_div_1);
  
  // Inicializar serial
  SetupSerial();
  SendSerialString("G502 X PLUS Spoofer iniciado");
  
  // Inicializar USB
  USB_Init();
  
  // Habilitar interrupções
  sei();
  
  // Loop principal
  while (1) {
    // Processar tarefas USB
    HID_Device_USBTask(&Mouse_HID_Interface);
    USB_USBTask();
    
    // Verificar serial
    if (Serial_IsCharReceived()) {
      char c = Serial_RxByte();
      ProcessSerialChar(c);
    }
  }
}

// Callback para criar relatório HID
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, uint8_t* const ReportID,
                                         const uint8_t ReportType, void* ReportData, uint16_t* const ReportSize) {
  uint8_t* MouseReport = (uint8_t*)ReportData;
  
  MouseReport[0] = MouseButtons;
  MouseReport[1] = MouseX;
  MouseReport[2] = MouseY;
  MouseReport[3] = MouseWheel;
  
  *ReportSize = 4;
  return true;
}

// Callback para processar relatório HID
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, const uint8_t ReportID,
                                          const uint8_t ReportType, const void* ReportData, const uint16_t ReportSize) {
  // Não usado neste exemplo
}

// Evento USB: Conexão
void EVENT_USB_Device_Connect(void) {
  SendSerialString("USB conectado");
}

// Evento USB: Desconexão
void EVENT_USB_Device_Disconnect(void) {
  SendSerialString("USB desconectado");
}

// Evento USB: Configuração alterada
void EVENT_USB_Device_ConfigurationChanged(void) {
  bool ConfigSuccess = true;
  
  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);
  USB_Device_EnableSOFEvents();
  
  SendSerialString("USB configurado");
}

// Evento USB: Requisição de controle
void EVENT_USB_Device_ControlRequest(void) {
  HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
}

// Evento USB: Start-of-Frame
void EVENT_USB_Device_StartOfFrame(void) {
  HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
}