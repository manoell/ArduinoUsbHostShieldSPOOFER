# Arduino Mouse Spoofer

Um projeto para fazer o Arduino Leonardo aparecer como um mouse Logitech G502 X PLUS aos sistemas operacionais e aplicações.

## Sumário

- [Introdução](#introdução)
- [Objetivos do Projeto](#objetivos-do-projeto)
- [Como Funciona](#como-funciona)
- [Requisitos](#requisitos)
- [Instalação](#instalação)
- [Implementação](#implementação)
- [Uso](#uso)
- [Dados Técnicos](#dados-técnicos)
- [Resolução de Problemas](#resolução-de-problemas)
- [Próximos Passos](#próximos-passos)
- [Licença](#licença)
- [Aviso Legal](#aviso-legal)

## Introdução

Este projeto modifica um Arduino Leonardo + USB Host Shield para aparecer como um mouse Logitech G502 X PLUS aos sistemas operacionais, aplicações e jogos. O projeto realiza um verdadeiro spoofing USB, alterando os descritores de baixo nível do dispositivo, incluindo VID (Vendor ID), PID (Product ID) e outras propriedades que identificam o dispositivo.

## Objetivos do Projeto

- Criar um dispositivo USB que seja identificado como um Logitech G502 X PLUS
- Passar por verificações de anti-cheats em jogos
- Entender e modificar descritores USB
- Preservar a funcionalidade do mouse original conectado ao USB Host Shield

## Como Funciona

O spoofing USB funciona modificando os descritores USB de baixo nível do Arduino Leonardo, que são utilizados durante o processo de enumeração USB. Quando conectado a um computador, o dispositivo se apresentará com os identificadores do Logitech G502 X PLUS em vez dos identificadores padrão do Arduino.

Este projeto vai além de simplesmente armazenar os valores em variáveis e responder a comandos AT - ele modifica o firmware USB para que o próprio sistema operacional reconheça o dispositivo como um mouse Logitech.

## Requisitos

### Hardware

- Arduino Leonardo R3
- USB Host Shield
- Mouse USB (para conectar ao Host Shield)
- Cabo USB

### Software

- Arduino IDE (versão mais recente)
- Bibliotecas:
  - HID-Project
  - USB Host Shield Library 2.0
  - EEPROM (inclusa no Arduino IDE)
- Ferramentas adicionais:
  - USBTreeView (ou similar) para verificação
  - Editor Hex (opcional)

## Instalação

1. Clone este repositório:
   ```
   git clone https://github.com/seu-username/arduino-mouse-spoofer.git
   ```
2. Abra o projeto no Arduino IDE
3. Instale as bibliotecas necessárias através do Gerenciador de Bibliotecas
4. Configure o Arduino IDE para programar o Arduino Leonardo
5. Carregue o firmware modificado para o Arduino

## Implementação

A implementação deste projeto envolve várias etapas críticas:

### 1. Modificação dos Descritores USB

O arquivo `USBDesc.h` na biblioteca core do Arduino é modificado para espelhar os descritores do Logitech G502 X PLUS:

```cpp
// Valores originais do Arduino Leonardo
// VID: 0x2341 (Arduino SA)
// PID: 0x8036

// Novos valores do Logitech G502 X PLUS
// VID: 0x046D (Logitech Inc.)
// PID: 0xC095
```

### 2. Configuração de Strings de Identificação

As strings descritoras são alteradas para corresponder ao mouse Logitech:

- Fabricante: "Logitech" (em vez de "Arduino LLC")
- Produto: "G502 X PLUS" (em vez de "Arduino Leonardo")
- Número de Série: Personalizado ou clonado

### 3. Configuração de Endpoints e Interfaces

Os endpoints e interfaces são configurados para corresponder ao mouse Logitech, que possui:
- 3 interfaces (comparado a 3 do Arduino original)
- 3 endpoints de entrada tipo Interrupt (comparado a diferente configuração do Arduino)

### 4. Integração com o Código de Controle do Mouse

O código de controle do mouse é adaptado para trabalhar com o novo perfil USB enquanto mantém a funcionalidade.

## Uso

1. Conecte o Arduino Leonardo ao computador via USB
2. Conecte seu mouse ao USB Host Shield
3. O Arduino aparecerá como um Logitech G502 X PLUS para o sistema
4. Os movimentos e cliques do mouse conectado serão replicados através do Arduino

Para verificar que o spoofing está funcionando corretamente:
- Verifique o Gerenciador de Dispositivos (Windows)
- Use ferramentas como USBTreeView ou USBDeview
- Verifique o reconhecimento em jogos ou aplicativos específicos

## Dados Técnicos

Abaixo estão os dados técnicos extraídos de ambos os dispositivos que são essenciais para o spoofing:

### Arduino Leonardo (Original)
- **VID (Vendor ID)**: 0x2341 (Arduino SA)
- **PID (Product ID)**: 0x8036
- **bcdDevice**: 0x0100
- **Fabricante**: "Arduino LLC"
- **Produto**: "Arduino Leonardo"
- **Número de Série**: "HIDLC"

### Logitech G502 X PLUS (Alvo)
- **VID (Vendor ID)**: 0x046D (Logitech Inc.)
- **PID (Product ID)**: 0xC095
- **bcdDevice**: 0x2700
- **Fabricante**: "Logitech"
- **Produto**: "G502 X PLUS"
- **Número de Série**: "4ED7923A"
- **Configuração**: "MPM27.00_B0016"

### Diferenças Estruturais Importantes
- O mouse Logitech tem 3 interfaces HID com 3 endpoints de entrada tipo Interrupt
- O Arduino tem uma configuração diferente de interfaces e endpoints
- Os valores bInterval (polling rate) do mouse são 1ms para todos os endpoints
- O Logitech inclui interfaces para mouse, teclado e um HID genérico

## Resolução de Problemas

**P: O sistema ainda detecta o dispositivo como Arduino**
R: Verifique se os descritores USB foram alterados corretamente. Certifique-se de modificar os arquivos corretos no firmware do Arduino.

**P: O dispositivo não é reconhecido**
R: É possível que a modificação tenha causado problemas na enumeração USB. Restaure o firmware original e tente novamente com alterações incrementais.

**P: O mouse conectado ao Host Shield não funciona**
R: Verifique as conexões e certifique-se de que o código está processando corretamente os eventos do mouse.

## Próximos Passos

- Implementar interface de configuração para alteração dinâmica de IDs
- Adicionar suporte para outros modelos de mouses
- Melhorar a compatibilidade com jogos específicos
- Implementar recursos avançados do mouse Logitech (DPI ajustável, botões extras)
- Criar interface gráfica para configuração

## Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para detalhes.

## Aviso Legal

Este projeto é destinado apenas para fins educacionais e de pesquisa. O uso deste projeto para contornar medidas de segurança, violar termos de serviço ou para qualquer atividade ilegal é estritamente proibido. Os autores não são responsáveis pelo uso indevido deste projeto.

O spoofing de dispositivos USB pode violar os termos de serviço de certos jogos ou serviços. Use por sua própria conta e risco.

---

## Apêndice: Detalhes Completos dos Dispositivos

### Arduino Leonardo
```
VID: 0x2341 (Arduino SA)
PID: 0x8036
Versão USB: 2.0 (Full-Speed)
Configurações: 1
Interfaces: 3
Endpoints utilizados: 5
Classe: Composto USB (EF/02/01)
```

### Logitech G502 X PLUS
```
VID: 0x046D (Logitech Inc.)
PID: 0xC095
Versão USB: 2.0 (Full-Speed)
Configurações: 1
Interfaces: 3
Endpoints utilizados: 4
Classe: Definida pela interface (00/00/00)
```

---

Criado com ❤️ para a comunidade maker e de jogos.
