# Home-Monitoring-System

Motivation

In the era of IOT, miniature home automation systems have become prevalent. However we also need to make sure that our house remains secure from various threats like Intruders, Fire, excessive water spillage, etc. These problems, if not notified at the right time, can create unnecessary destruction of precious resources and theft. This provides a strong motivation to work on such a project. 


Block Diagram


Circuit Diagram


In this project, we will build a security system which can trigger email to the owner of the house in case there is intrusion, fire or water spill in the house. For this purpose, we will use the following modules: 
1. ESP8266 module (for internet connectivity over TCP/IP) 
2. PIR Sensor (for detecting presence of an intruder)  
3. ISD1820 voice module (for sending voice message alert) 
4. DHT11 Temperature & Humidity sensor (for detecting excessive heat) 
5. HCSR04 Ultrasonic Sensor (for monitoring water level in tanks)   

Whenever any of these sensors are triggered, the user will be immediately notified via email. This will be helpful in monitoring the home while the owner is away.
