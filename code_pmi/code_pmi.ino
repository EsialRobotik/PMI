
#include "DynamixelSerial.h"
#define TEMPO 90000
//#define TEMPO 10000
#define ID 5

const int tirettePin = 4;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int sensorValue = 0;
int state = 0;
const long tempo = TEMPO ;

void setup() {
  pinMode(tirettePin, INPUT);
  Dynamixel.begin(115200, ID);
  Serial.begin(115200);
  state = 0;
  Dynamixel.move(ID, 0);
}

void fire() {
  Dynamixel.move(ID, 650);
  delay(1000);
  Dynamixel.move(ID, 100);
  delay(1000);
  Dynamixel.move(ID, 700);
  delay(1000);
  Dynamixel.move(ID, 0);
}

void loop() {
  if (tempo != TEMPO) {
    Serial.println("Tempo != 90s !!!!!!");
  }
  sensorValue = digitalRead(tirettePin);
  Serial.println(sensorValue);
  switch (state) {

    case 0 :
      state++;
      break;

    case 1:
      //attente tirette
      Serial.println("attente tirette\n");

      if (sensorValue == LOW) {
        //passage en attente départ
        state ++;
      }
      break;


    case 2:
      //attente depart
      Serial.println("attente depart\n");
      if (sensorValue == HIGH) {
        //passage en mode attente depart match
        state ++;
      }
      break;


    case 3:
      //match
      Serial.println("match\n");
      delay(tempo + 1000);
      state++;
      break;

    case 4:
      //servo
      Serial.println("servo\n");
      fire();
      delay(500);                       // waits 15ms for the servo to reach the position

      state++;
      break;
    default :
      //wait until end of time
      Serial.println("match fini !!!\n");
      break;




  }

}

