#include <Mouse.h> 
#include <Wire.h> 
#include <SPI.h> 
#include <usbhub.h> 
USB     Usb; 
USBHub     Hub(&Usb); 
 
byte bf[2];
 
#include <hidboot.h> 
 
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb); 
 
String myString;  
int j = 0; 
int c = 0; 
int e = 0; 
int lmb = 0; 
int rmb = 0; 
int mmb = 0; 
int dx; 
int dy; 
int arr[2]; 
int arrv[8]; 

int smurf_dx;
int smurf_dy;
int dxn;
int dyn;
int index;
int num_size;
int jump = 127;
//String tmp;


 
class MouseRptParser : public MouseReportParser 
 
{ 
 
  protected: 
 
    void OnMouseMove  (MOUSEINFO *mi); 
 
    void OnLeftButtonUp (MOUSEINFO *mi); 
 
    void OnLeftButtonDown (MOUSEINFO *mi); 
 
    void OnRightButtonUp  (MOUSEINFO *mi); 
 
    void OnRightButtonDown  (MOUSEINFO *mi); 
 
    void OnMiddleButtonUp (MOUSEINFO *mi); 
 
    void OnMiddleButtonDown (MOUSEINFO *mi); 
 
}; 
 
 
void MouseRptParser::OnMouseMove(MOUSEINFO *mi) 
 
{ 
 
  dx = mi->dX; 
 
  dy = mi->dY; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) 
 
{ 
 
  lmb = 0; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) 
 
{ 
 
  lmb = 1; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) 
 
{ 
 
  rmb = 0; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi) 
 
{ 
 
  rmb = 1; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) 
 
{ 
 
  mmb = 0; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi) 
 
{ 
 
  mmb = 1; 
 
}; 
  
MouseRptParser  Prs; 
 
void setup() {
 
  delay(5000); 
  Mouse.begin(); 
  Serial.begin(115200); 
  Serial.setTimeout(1);
   
  Usb.Init(); 
  HidMouse.SetReportParser(0, &Prs); 
  } 
 
void loop() {
  dx = 0; 
 
  dy = 0; 
 
   
 
  j = 0; 
 
  c = 0; 
 
  e = 0; 
 
     
 
  Usb.Task(); 
 
  
 
  //Clicking 
 
  if (lmb == 0){ 
 
    Mouse.release(MOUSE_LEFT); 
 
    } 
 
     
 
  else if (lmb == 1){ 
 
    Mouse.press(MOUSE_LEFT); 
 
    } 
 
  
 
  if (rmb == 0){ 
 
    Mouse.release(MOUSE_RIGHT); 
 
    } 
 
     
 
  else if (rmb == 1){ 
 
    Mouse.press(MOUSE_RIGHT); 
 
    } 
 
  
 
  if (mmb == 0){ 
 
    Mouse.release(MOUSE_MIDDLE); 
 
    } 
 
     
 
  else if (mmb == 1){ 
 
    Mouse.press(MOUSE_MIDDLE); 
 
    } 
	
	
	
  if (Serial.available() > 0 && Serial.available() != 4)
  {
	  String smurfed = Serial.readString();
	  
     if (smurfed.substring(0,6) == "syl3nt")
        {
            smurfed.remove(0,6);
            index = 0;
            num_size = smurfed.indexOf(":", index);
            smurf_dx = smurfed.substring(index,num_size).toInt();
            smurfed.remove(0,num_size+1);
            smurf_dy = smurfed.toInt();
            dxn = smurf_dx *-1;
            dyn = smurf_dy *-1;

            if (smurf_dx > 0){
                while (smurf_dx > 127)
                {
                    smurf_dx -= 127;
                    Mouse.move(127,0);
                }
                Mouse.move(smurf_dx,0);
            }
            else if (smurf_dx < 0){
                while (smurf_dx < -127)
                {
                    smurf_dx += 127;
                    Mouse.move(-127,0);
                }
                Mouse.move(smurf_dx,0);
            }
            if (smurf_dy > 0){
                while (smurf_dy > 127)
                {
                    smurf_dy -= 127;
                    Mouse.move(0,127);
                }
                Mouse.move(0,smurf_dy);
            }
            else if (smurf_dy < 0){
                while (smurf_dy < -127)
                {
                    smurf_dy += 127;
                    Mouse.move(0,-127);
                }
                Mouse.move(0,smurf_dy);
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



     else if (smurfed.substring(0,6) == "movsht")
        {
            smurfed.remove(0,6);
            index = 0;
            num_size = smurfed.indexOf(":", index);
            smurf_dx = smurfed.substring(index,num_size).toInt();
            smurfed.remove(0,num_size+1);
            smurf_dy = smurfed.toInt();
            dxn = smurf_dx *-1;
            dyn = smurf_dy *-1;

            if (smurf_dx > 0){
                while (smurf_dx > 127)
                {
                    smurf_dx -= 127;
                    Mouse.move(127,0);
                }
                Mouse.move(smurf_dx,0);
            }
            else if (smurf_dx < 0){
                while (smurf_dx < -127)
                {
                    smurf_dx += 127;
                    Mouse.move(-127,0);
                }
                Mouse.move(smurf_dx,0);
            }
            if (smurf_dy > 0){
                while (smurf_dy > 127)
                {
                    smurf_dy -= 127;
                    Mouse.move(0,127);
                }
                Mouse.move(0,smurf_dy);
            }
            else if (smurf_dy < 0){
                while (smurf_dy < -127)
                {
                    smurf_dy += 127;
                    Mouse.move(0,-127);
                }
                Mouse.move(0,smurf_dy);
            }
            Mouse.click();

        }






















 
  }	
	
	
	
	
	
	
    else if (Serial.available() > 0 && Serial.available() == 4) {
        byte bytes[4];
        for (byte i = 0; i < 4; i++) {
          bytes[i] = Serial.read();
        }
        if ( (bytes[0] == 0x7E) && (bytes[3] == 0x7E)) {
		  uint8_t data[2];
          data[0] = bytes[1];
          data[1] = bytes[2];
          Mouse.move(data[0], data[1], 0);
        }

        if ( (bytes[0] == 0x7B) && (bytes[3] == 0x7B)) {
		  uint8_t data[2];
          data[0] = bytes[1];
          data[1] = bytes[2];
          Mouse.move(-data[0], -data[1], 0);
        }

        if ( (bytes[0] == 0x5E) && (bytes[3] == 0x5E)) {
          Mouse.click(); 

        }
	  
    }		
 
  
   else { 
 
    Mouse.move(dx, dy); 
 
    } 
}
