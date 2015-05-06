#include <Stepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>
// change this to the number of steps on your motor
#define STEPS 200
#define SERVOPIN 9
#define SPEED 60

#define REDSTEPS -50
#define GREENSTEPS -100
#define BLUESTEPS 50

#define RXPIN 10
#define TXPIN 11

#define TEST 0
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 4, 5, 6, 7);
SoftwareSerial ReceivePort(RXPIN,TXPIN);
boolean tested = false;
Servo servo;
 
void setup()
{
  Serial.begin(9600);
  ReceivePort.begin(4800);
  Serial.println("This is the Sorter Arm!");
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(SPEED);
  servo.attach(SERVOPIN);
  
}
 
void loop()
{
  
  if (ReceivePort.available()) {
    uint16_t color = ReceivePort.read();
    Serial.println(color);
    if(color == 114)
    {
      dumpRed();
    }
    else if (color == 103)
    {
      dumpGreen();
    }
    else if (color == 98)
    {
       dumpBlue(); 
    }
  }
}

void dumpRed(){
 servo.write(0);
 delay(100);
 stepper.step(REDSTEPS);
 delay(1000);
 servo.write(180);
 delay(1000);
 servo.write(0);
 delay(1000);
 stepper.step(-REDSTEPS);
}

void dumpGreen(){
 servo.write(0);
 delay(100);
 stepper.step(GREENSTEPS);
 delay(1000);
 servo.write(180);
 delay(1000);
 servo.write(0);
 delay(1000);
 stepper.step(-GREENSTEPS);
 delay(1000);
}

void dumpBlue(){
 servo.write(0);
 delay(100);
 stepper.step(BLUESTEPS);
 delay(1000);
 servo.write(180);
 delay(1000);
 servo.write(0);
 delay(1000);
 stepper.step(-BLUESTEPS);
 delay(1000);
}

void test(){
 if(!tested){
    
  //Serial.println("Forward");
  //stepper.step();
  Serial.println("Backward");
  //delay(500);
  servo.write(0);
  delay(100);
  stepper.step(STEPS);
  delay(1000);
  stepper.step(-STEPS);
  delay(1000);
  servo.write(180);
  //you need a delay between rotations or it doesnt do anything
  delay(1000);
  servo.write(0);
  tested = true;
  } 
}
