# Nome do projeto
TARGET = G502_Spoofer
# Tipo de MCU
MCU = atmega32u4
# Frequência do cristal em Hz
F_CPU = 16000000
# Frequência do cristal USB em Hz
F_USB = 16000000
# Arquitetura do chip
ARCH = AVR8
# Placa
BOARD = LEONARDO
# Tipo de otimização
OPT = s
# Caminho para a biblioteca LUFA
LUFA_PATH = ./LUFA

# Inclusão do makefile LUFA comum
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

# Arquivos fonte do projeto
SRC = $(TARGET).c Descriptors.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)

# Inclusões
LUFA_OPTS = -D USB_DEVICE_ONLY
LUFA_OPTS += -D USE_FLASH_DESCRIPTORS
LUFA_OPTS += -D USE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"
LUFA_OPTS += -D F_USB=$(F_USB)UL

# Opções de compilador
CFLAGS += -D F_CPU=$(F_CPU)UL
CFLAGS += -D BOARD=BOARD_$(BOARD)
CFLAGS += $(LUFA_OPTS)
CFLAGS += -I Config/
CFLAGS += -I$(LUFA_PATH)/

# Upload para o Arduino Leonardo
AVRDUDE_PROGRAMMER = avr109
AVRDUDE_PORT = COM3  # Altere para a porta do seu Arduino
AVRDUDE_FLAGS = -b 57600