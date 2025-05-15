#include <usbhid.h>
#include <Mouse.h>
#include <hiduniversal.h>
#include <SPI.h>
#include "hidmouserptparser.h"
#include <Keyboard.h>

static const int8_t ZERO = 127;
static const int8_t MIN_VALUE = -127;
static const int8_t MAX_VALUE = 127;

USB Usb;
//USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
HIDMouseEvents MouEvents;
HIDMouseReportParser Mou(&MouEvents);

int dx;
int dy;
int dxn;
int dyn;
int index;
int num_size;
int jump = 127;
//String tmp;

void setup() {
  Mouse.begin();
  Serial.begin(115200);
  //#if !defined(__MIPSEL__)
  //  while (!Serial); //Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  //#endif
  //Serial.println("Start");
  Serial.println("Start");
  Serial.setTimeout(0);

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");
    delay(200);

  if (!Hid.SetReportParser(0, &Mou))
    ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop() {
	
/*	if (Serial.available())
    {
	String data = Serial.readString();
	  if (data =="shttt")
	  {
         Mouse.click();
      }
	  
	  if (data =="cheese" )
		
		{
			
           Keyboard.press('o');
		   delay(50);
		   Keyboard.release('o');
        }	
	    
	}
*/	
  //mouse_task();
  Usb.Task();
  mouse_task();
  
}

void mouse_task() {
  uint8_t recv[2];
  
  if (Serial.available() > 0 && Serial.available() != 4)
  {
	  String data = Serial.readString();
	  
if (data.substring(0,6) == "syl3nt")
        {
            data.remove(0,6);
            index = 0;
            num_size = data.indexOf(":", index);
            dx = data.substring(index,num_size).toInt();
            data.remove(0,num_size+1);
            dy = data.toInt();
            dxn = dx *-1;
            dyn = dy *-1;

            if (dx > 0){
                while (dx > 127)
                {
                    dx -= 127;
                    Mouse.move(127,0);
                }
                Mouse.move(dx,0);
            }
            else if (dx < 0){
                while (dx < -127)
                {
                    dx += 127;
                    Mouse.move(-127,0);
                }
                Mouse.move(dx,0);
            }
            if (dy > 0){
                while (dy > 127)
                {
                    dy -= 127;
                    Mouse.move(0,127);
                }
                Mouse.move(0,dy);
            }
            else if (dy < 0){
                while (dy < -127)
                {
                    dy += 127;
                    Mouse.move(0,-127);
                }
                Mouse.move(0,dy);
            }
            Mouse.click();
            if (dxn > 0){
                while (dxn > 127)
                {
                    dxn -= 127;
                    Mouse.move(127,0);
                }
                Mouse.move(dxn,0);
            }
            else if (dxn < 0){
                while (dxn < -127)
                {
                    dxn += 127;
                    Mouse.move(-127,0);
                }
                Mouse.move(dxn,0);
            }
            if (dyn > 0){
                while (dyn > 127)
                {
                    dyn -= 127;
                    Mouse.move(0,127);
                }
                Mouse.move(0,dyn);
            }
            else if (dyn < 0){
                while (dyn < -127)
                {
                    dyn += 127;
                    Mouse.move(0,-127);
                }
                Mouse.move(0,dyn);
            }
        }	  
	  
	  
else if (data.substring(0,6) == "movsht")
        {
            data.remove(0,6);
            index = 0;
            num_size = data.indexOf(":", index);
            dx = data.substring(index,num_size).toInt();
            data.remove(0,num_size+1);
            dy = data.toInt();
            dxn = dx *-1;
            dyn = dy *-1;

            if (dx > 0){
                while (dx > 127)
                {
                    dx -= 127;
                    Mouse.move(127,0);
                }
                Mouse.move(dx,0);
            }
            else if (dx < 0){
                while (dx < -127)
                {
                    dx += 127;
                    Mouse.move(-127,0);
                }
                Mouse.move(dx,0);
            }
            if (dy > 0){
                while (dy > 127)
                {
                    dy -= 127;
                    Mouse.move(0,127);
                }
                Mouse.move(0,dy);
            }
            else if (dy < 0){
                while (dy < -127)
                {
                    dy += 127;
                    Mouse.move(0,-127);
                }
                Mouse.move(0,dy);
            }
            Mouse.click();

        }		  
	  
	  
	  
	  
  }	  
	
  else
  {
	   
  
  
  
  if (polling_data(recv)) {
    int8_t moves[2];
    if (parse_data(&moves[0], &moves[1], &recv[0], &recv[1])) {
      Mouse.move(moves[0], moves[1], 0);
    }		
  }








/*  
    if (polling_silenzio(recv)) {
    int8_t moves[2];
    if (parse_data(&moves[0], &moves[1], &recv[0], &recv[1])) {
      Mouse.move(moves[0], moves[1], 0);
	  Mouse.click(); 
	  Mouse.move(-moves[0], -moves[1], 0);
    }		
  }
*/  
 

 
  
/*  
  if (polling_inverso(recv)) {
    int8_t moves[2];
    if (parse_data(&moves[0], &moves[1], &recv[0], &recv[1])) {
      Mouse.move(-moves[0], -moves[1], 0);
    }		
  }  
*/  
  
  if (polling_shttt(recv)) {
     Mouse.click(); 
  } 
	  
	  
	  
	  
	  
	  
	  
	  
  }  
	
	

}

bool polling_data(uint8_t *data) {
  if (Serial.available() > 0) { // >=4
    byte bytes[4];
    for (byte i = 0; i < 4; i++) {
      bytes[i] = Serial.read();
    }
    if ( (bytes[0] == 0x7E) && (bytes[3] == 0x7E)) {
      data[0] = bytes[1];
      data[1] = bytes[2];
      return true;
    }
  }
  return false;
}


bool polling_silenzio(uint8_t *data) {
  if (Serial.available() > 0) { // >=4
    byte bytes[4];
    for (byte i = 0; i < 4; i++) {
      bytes[i] = Serial.read();
    }
    if ( (bytes[0] == 0x7C) && (bytes[3] == 0x7C)) {
      dx = bytes[1];
      dy = bytes[2];
      return true;
    }
  }
  return false;
}

/*
bool polling_silenzio(uint8_t *data) {
  if (Serial.available() > 0) { // >=4
    byte bytes[4];
    for (byte i = 0; i < 4; i++) {
      bytes[i] = Serial.read();
    }
    if ( (bytes[0] == 0x7C) && (bytes[3] == 0x7C)) {
      data[0] = bytes[1];
      data[1] = bytes[2];
      return true;
    }
  }
  return false;
}
*/


bool polling_shttt(uint8_t *data) {
  if (Serial.available() > 0) { // >=4
    byte bytes[4];
    for (byte i = 0; i < 4; i++) {
      bytes[i] = Serial.read();
    }
    if ( (bytes[0] == 0x5E) && (bytes[3] == 0x5E)) {
      //data[0] = bytes[1];
      //data[1] = bytes[2];
      return true;
    }
  }
  return false;
}


/*
bool polling_inverso(uint8_t *data) {
  if (Serial.available() > 0) { // >=4
    byte bytes[4];
    for (byte i = 0; i < 4; i++) {
      bytes[i] = Serial.read();
    }
    if ( (bytes[0] == 0x7B) && (bytes[3] == 0x7B)) {
      //data[0] = bytes[1];
      //data[1] = bytes[2];
      return true;
    }
  }
  return false;
}
*/

bool parse_data(int8_t *mouse_x, int8_t *mouse_y, uint8_t *read_x, uint8_t *read_y) {
  if ( (*mouse_x != ZERO) || (*mouse_y != ZERO) ) {
    *mouse_x = *read_x - ZERO;
    *mouse_y = *read_y - ZERO;
    data_correction(mouse_x, mouse_y);
    return true;
  }
  return false;
}

void data_correction(int8_t *mouse_x, int8_t *mouse_y) {
  if (*mouse_x <= MIN_VALUE) {
    *mouse_x = MIN_VALUE;
  }
  if (*mouse_x >= MAX_VALUE) {
    *mouse_x = MAX_VALUE;
  }
  if (*mouse_y <= MIN_VALUE) {
    *mouse_y = MIN_VALUE;
  }
  if (*mouse_y >= MAX_VALUE) {
    *mouse_y = MAX_VALUE;
  }
}
