#include <Servo.h>
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;

BTD Btd(&Usb); 
PS4BT PS4(&Btd, PAIR);
bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
int m1=2;
int m2=4;
int m3=7;
int m4=8;
int e1=5;
int e2=9;

int pos1;
int pos2;

char inChar;
signed int speed1, speed2;
int clockwise;
Servo myservo1;
Servo myservo2;


void setup() {
  Serial.begin(115200);
 
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m4,OUTPUT);
pinMode(e1,OUTPUT);
pinMode(e2,OUTPUT);
 myservo1.attach(10);
  myservo2.attach(11);  

}
void loop() {
  Usb.Task();

  if (PS4.connected()) {
    if(PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117)
    {
    if (PS4.getAnalogHat(LeftHatY)<117)//forward
    {

    int clockwise=PS4.getAnalogHat(LeftHatY);
     speed1=map(clockwise,117,0,0,250);
    analogWrite(e1,speed1);
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    Serial.print(PS4.getAnalogHat(LeftHatY));
   
    analogWrite(e2,speed1);
    
    }
    else if (PS4.getAnalogHat(LeftHatY)>137)//backward
    {
     clockwise=PS4.getAnalogHat(LeftHatY);
     speed1=map(clockwise,137,255,0,250); 
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);  
    Serial.print(PS4.getAnalogHat(LeftHatY));  
      
    analogWrite(e1,speed1);
    analogWrite(e2,speed1); 
  
    }
     else if (PS4.getAnalogHat(LeftHatX)<117)//LEFT
    {
    clockwise=PS4.getAnalogHat(LeftHatX);
     Serial.print(PS4.getAnalogHat(LeftHatX));  
      speed1=map(clockwise,117,0,0,250);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);    
    
    analogWrite(e1,speed1);
    analogWrite(e2,speed1);
    
    }
     else if (PS4.getAnalogHat(LeftHatX)>137)//RIGHT
    {
    clockwise=PS4.getAnalogHat(LeftHatX);
     Serial.print(PS4.getAnalogHat(LeftHatX));  
       speed1=map(clockwise,137,255,0,250);
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);    
   
    analogWrite(e1,speed1);
    analogWrite(e2,speed1);
    
    }
    else
    {
     
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
     digitalWrite(m3,LOW);
    digitalWrite(m3,LOW);
    speed1=0;
    analogWrite(e1,speed1);
    analogWrite(e2,speed1);
     
    }
    }
      if(PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117)
    {
        if(PS4.getAnalogHat(RightHatY) < 117)
        {
           pos1=PS4.getAnalogHat(RightHatY);
            myservo1.write(map(pos1,117,0,60,120));           
             
                
        }
        else if(PS4.getAnalogHat(RightHatY) > 137)
        {
           pos1=PS4.getAnalogHat(RightHatY);
            myservo1.write(map(pos1,137,255,120,60)); 
        }
    }
      if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2))
      {
         if(PS4.getAnalogButton(L2)>20 )
        {
           pos1= PS4.getAnalogButton(R2);
            myservo2.write(map(pos1,20,255,60,120));           
             
                
        }
        else if( PS4.getAnalogButton(R2)>20)
        {
           pos1= PS4.getAnalogButton(R2);
            myservo2.write(map(pos1,20,255,120,60)); 
        }
      }
    
  
else
    {
     
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
     digitalWrite(m3,LOW);
    digitalWrite(m3,LOW);
    speed1=0;
     analogWrite(e1,speed1);
    analogWrite(e2,speed1);
    
    }
  }
}
