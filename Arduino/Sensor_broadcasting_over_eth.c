#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
#define DHTPIN 8
#define DHTTYPE DHT11

DHT sensor(DHTPIN, DHTTYPE);

int inputPin = 5;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
char* s[]={"Motion Detected!","Motion Ended!"};
char* chacha;
const int trigPin = 6;
const int echoPin = 7;
long duration;
int distance;

byte mac[] = {
               0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
             };

IPAddress ip(10, 20, 14, 88);
EthernetServer server(80);
 
void setup() 
{
  // for ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  
  Serial.begin (9600);
  sensor.begin( );
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin( );
  Serial.print("Your IP Adress is ");
  Serial.println(Ethernet.localIP( ) );
}

void loop( ) 
{
  float humidity = sensor.readHumidity( );
  float temperature_C = sensor.readTemperature( );
  Serial.print("Temperature in C: ");
  Serial.println(temperature_C);
  float temperature_F = sensor.readTemperature (true);
  Serial.print("Temperature in F: "); 
  Serial.println(temperature_F);

  if (isnan(humidity) || isnan(temperature_C) || isnan(temperature_F)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float heat_indexF = sensor.computeHeatIndex(temperature_F, humidity);
  Serial.print("Heat index in F: ");  
  Serial.println(heat_indexF);
  float heat_indexC = sensor.convertFtoC(heat_indexF);
  Serial.print("Heat index in C: ");
  Serial.println(heat_indexC);
  
   val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      chacha=s[0];
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    //digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned off
      chacha=s[1];
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

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
   
  EthernetClient webpage = server.available();
  if (webpage) 
    {
      Serial.println("new webpage");
      boolean currentLineIsBlank = true;
      while (webpage.connected ( ) ) 
        {
          if (webpage.available ( ) ) 
            {
              char character = webpage.read ( );
              Serial.write(character);
              if (character == '\n' && currentLineIsBlank) 
                {
                  webpage.println ("HTTP/1.1 200 OK");
                  webpage.println ("Content-Type: text/html");
                  webpage.println ("Connection: close");
                  webpage.println ("Refresh: 5");
                  webpage.println ( );
                  webpage.println ("<!DOCTYPE HTML>");
                  webpage.println ("<html>");
                  webpage.print ("<Title>Arduino Ethernet Webserver </Title>");
                  webpage.print ("<h1>Arduino Ethernet Shield Webserver </h1>");
                 // webpage.print ("<h3><a href='http://electrosome.com'>Visit us for Amazing 
                 //                 Projects</a> </h3>");
                  webpage.print ("<h4>Temperature in C: ");
                  webpage.print (temperature_C);
                  webpage.print ("</h4><h4>Temperature in Fah: ");
                  webpage.print (temperature_F);
                  webpage.print ("</h4><h4>Humidity: ");
                  webpage.print (humidity);
                  webpage.print ("</h4><h4>Heat Index in F: ");
                  webpage.println (heat_indexF);
                  webpage.println ("</h4><h4>Heat Index in C: ");
                  webpage.println (heat_indexC);
                  webpage.println ("</h4><h4>Motion: ");
                  webpage.println (chacha);
                  webpage.println ("</h4><h4>Distance: ");
                  webpage.println (distance); 
                  webpage.println ("<br />");
                  webpage.println ("</html>");
                  break;
                }
                 
                if ( character == '\n') 
                  {
                    currentLineIsBlank = true;
                  } 
                else if (character != '\r') 
                  {
                    currentLineIsBlank = false;
            }
        }
    }
    delay(1);
    webpage.stop();
    Serial.println("webpage disconnected");
  }
  //chacha="";
}
