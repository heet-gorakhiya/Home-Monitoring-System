#include "DHT.h"
//#define dataPin 8 // Defines pin number to which the sensor is connected
#define DHTPIN 13 // what digital pin we're connected to
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int inputPin = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  // for ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  //for dht 11 
  Serial.begin(9600);
  dht.begin();

  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);

}

void loop() {
   // put your main code here, to run repeatedly:
   // Clears the trigPin

   //for water level detection
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   // Sets the trigPin on HIGH state for 10 micro seconds
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   // Reads the echoPin, returns the sound wave travel time in microseconds
   duration = pulseIn(echoPin, HIGH);
   // Calculating the distance
   distance= duration*0.034/2;
   if (distance < 20)
   {
      Serial.print("Level Reached");
   }
   
   // Prints the distance on the Serial Monitor
   Serial.print("Distance: ");
   Serial.println(distance);


   //for dht 11
   float t = dht.readTemperature(); // Gets the values of the temperature
   if (isnan(t) /*|| isnan(f)*/) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    } 

   Serial.print("Temperature = ");
   Serial.print(t);
   Serial.print(" *C\n ");

   delay(2000);
   
   //pir sensor
   val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    //digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
