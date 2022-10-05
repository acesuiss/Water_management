
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"


// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define Motorpin 4

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int Water_level();
void online();
void offline();
void manuval();
void Auto();
BLYNK_WRITE(v0){
  int modes = param.asInt();
}
BLYNK_WRITE(v2){
  int Motorstate = param.asInt();
  digitalWrite(motorpin,Motor);
}
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(Motorpin, OUTPUT);
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  delay(100);
  BlynkEdgent.begin();
}

void loop() {
   if(WiFi.status() != WL_CONNECTED){
    offline();
    }
    else
    online();
    BlynkEdgent.run();
}

int Water_level(){
    // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  return distance ;
  }
void offline (){
  if (Waterlevel() < 40 && Waterlevel() < 10 )
    digitalWrite(Motorpin,HIGH);
  else
    digitalWrite(Motorpin,LOW);
  }
void online (){
  if (modes == 1)
    Auto();
  if (modes == 0)
    manuval();
}


void Auto(){
  if (Waterlevel() < 40 && Waterlevel() < 10 ){
    digitalWrite(Motorpin,HIGH);
    Blynk.virtualWrite(V1,waterlevel());
    
    }
  else
     digitalWrite(Motorpin,LOW);
     Blynk.virtualWrite(V1,waterlevel());
}
void manuval(){
  
  digitalWrite(motorpin,motorstate);
}
