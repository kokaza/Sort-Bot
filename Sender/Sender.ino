//Sender Arduino 1
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define RXPIN 10
#define TXPIN 11
#define BUTTONPIN 2
#define OFFSET 10

SoftwareSerial SendPort(RXPIN,TXPIN);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);


void setup(){
  Serial.begin(9600); 
  SendPort.begin(4800);
  pinMode(BUTTONPIN, INPUT);
  Serial.println("This is the Sender");
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}

void loop(){
 int buttonState;
 digitalWrite(13,LOW);
 buttonState = digitalRead(BUTTONPIN);
 if(buttonState == LOW){
 digitalWrite(13,HIGH);
 delay(500);
 uint16_t clear, red, green, blue;
 
 tcs.setInterrupt(false);
 delay(60);
 tcs.getRawData(&red,&green,&blue,&clear);
 tcs.setInterrupt(true);
 
 Serial.print("C:\t"); Serial.print(clear);
 Serial.print("\tR:\t"); Serial.print(red);
 Serial.print("\tG:\t"); Serial.print(green);
 Serial.print("\tB:\t"); Serial.print(blue);
 Serial.println();
 red = red - OFFSET;
 
 //aThis is for red
 if(red > green && red >blue)
 {
   SendPort.print("r");
   Serial.print("r");
 }else if(green > red && green > blue)
 {
   SendPort.print("g");
   Serial.print("g");
 }else if(blue > red && blue > green)
 {
   SendPort.print("b");
   Serial.print("b");
 }
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW); 
 delay(3000);
 }
}
