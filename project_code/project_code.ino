//Importing the servo library
#include <Servo.h>
// create an instance 
Servo myServo;

//Creating constants to name inputs and outputs 
const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;

//Creating variables to hold the values from switch and piezo
int knockVal;
int switchVal;

//Knock maximum and minimum levels
const int quietKnock = 10;
const int loudKnock = 100;

//To know if the lock is engaged or not
boolean locked = false;
//How many knocks you've received
int numberOfKnocks = 0;


void setup(){
  myServo.attach(9);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  digitalWrite(greenLed, HIGH);
  myServo.write(0);
  Serial.println("the box is unlocked");
  }

  void loop(){
    if(locked==false){
      switchVal = digitalRead(switchPin);
      if(switchVal == HIGH){
        locked = true;
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);
        myServo.write(90);
        Serial.println(90);
        Serial.println("The box is locked");
        delay(1000);
        
      }
      }
      if(locked == true){
        knockVal = analogRead(piezo);
        if(numberOfKnocks < 3 && knockVal > 0){
          if(checkForKnock(knockVal) == true){
            numberOfKnocks++;
          }
          Serial.print(3-numberOfKnocks);
          Serial.println(" more knocks to go");
          }
         if(numberOfKnocks>=3){
          locked= false;
          myServo.write(0);
          delay(20);
          digitalWrite(greenLed,HIGH);
          digitalWrite(redLed,LOW);
          Serial.println("the box is unlocked");
          numberOfKnocks = 0;
         } 
       }
    }

 boolean checkForKnock(int value){
  if(value > quietKnock && value < loudKnock){
    digitalWrite(yellowLed, HIGH);
    delay(50);
    digitalWrite(yellowLed, LOW);
    Serial.print("Valid knock of value");
    Serial.println(value);
    return true;
  }
 else{
  Serial.print("Bad knock value");
  Serial.print(value);
  return false;
   }
  }
