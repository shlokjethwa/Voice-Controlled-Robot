#include <NewPing.h>
#include <AFMotor.h> 
#define ECHO_PIN 
#define MAX_DISTANCE 300 
#define MAX_SPEED 160 
#define MAX_SPEED_OFFSET 40 
#define COLL_DIST 30 
#define TURN_DIST COLL_DIST+20 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
AF_DCMotor motor3 (3, MOTOR34_1KHZ); 
AF_DCMotor motor4 (4, MOTOR34_1KHZ); 
Servo myServo; 
String voice;
int leftDistance, rightDistance; 
int curDist = 0;
String motorSet = "";
int speedSet = 0;


void setup()
{
  Serial.begin(9600);
  myServo.attach(10); 
  myServo.write(90); 
 }
void loop() 
{
while (Serial.available()){ 
     delay(10); 
    char c = Serial.read();    if (c == '#') {break;}
    voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0){
    if(voice == "*go ahead"){
      myServo.write(90);  
      delay(90);
      curDist = readPing();   
      if (curDist < COLL_DIST) 
      {changePath();}
      forward_car();
    }
    else if(voice == "*go back"){
      back_car();
    }
    else if(voice == "*turn right") {
      myServo.write(90);  
      delay(90);
      curDist = readPing();   
      if (curDist < COLL_DIST) 
      {changePath();}
      right_car();
    }
    else if(voice == "*turn left") {
      myServo.write(90);  
      delay(90);
      curDist = readPing();   
      if (curDist < COLL_DIST) 
      {changePath();}
      left_car();
    }
else if(voice =="*turn little left"){
      myServo.write(45);
      delay(45);
      little_left_car();
    }
    else if(voice =="*turn little right"){
      myServo.write(45);
      delay(45);
      little_right_car();
    }
    else if(voice == "*stop") {
      stop_car();
    }
    else if(voice =="*turn around"){
      turn_around();
    }
    voice=""; 
  }
}
void changePath() {
  stop_car();
}
int readPing() {  
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}
void forward_car()
{motor3.run(FORWARD);
  motor3.setSpeed(210);
  motor4.run(FORWARD);
  motor4.setSpeed(210);
  delay(2000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);}
 void back_car()
{motor3.run(BACKWARD);
  motor3.setSpeed(210);
  motor4.run(BACKWARD);
  motor4.setSpeed(210);
  delay(2000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);}
void right_car()
{
  myServo.write(0);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor4.run(FORWARD);
  motor4.setSpeed(100);
  motor3.run(BACKWARD);
  motor3.setSpeed(100);
  delay(1000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void left_car()
{
  myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor4.run(BACKWARD);
  motor4.setSpeed(100);
  motor3.run(FORWARD);
  motor3.setSpeed(100);
  delay(1000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void little_left_car()
{
  myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor4.run(BACKWARD);
  motor4.setSpeed(80);
  motor3.run(FORWARD);
  motor3.setSpeed(80);
  delay(1000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}
void little_right_car()
{
  myServo.write(0);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor4.run(FORWARD);
  motor4.setSpeed(80);
  motor3.run(BACKWARD);
  motor3.setSpeed(80);
  delay(1000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  }
void turn_around()
{
  myServo.write(0);
  delay(1000);
  myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor4.run(FORWARD);
  motor4.setSpeed(250);
  motor3.run(BACKWARD);
  motor3.setSpeed(250);
 }
void stop_car ()
{
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
