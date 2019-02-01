# Home-Monitoring-System

## Motivation

In the era of IOT, miniature home automation systems have become prevalent. However we also need to make sure that our house remains secure from various threats like Intruders, Fire, excessive water spillage, etc. These problems, if not notified at the right time, can create unnecessary destruction of precious resources and theft. This provides a strong motivation to work on such a project. 


## Block Diagram

![Block Diagram](https://github.com/Grimmjaw6/Home-Monitoring-System/blob/master/BlockDiag.PNG)

## Circuit Diagram

### Arduino



### RaspberryPi

![Circuit Diagram](https://github.com/Grimmjaw6/Home-Monitoring-System/blob/master/Circuit%20Diagram.PNG)

## Description

In this project, we will build a security system which can trigger email to the owner of the house in case there is intrusion, fire or water spill in the house. For this purpose, we will use the following modules: 
1. Ethernet Module (for internet connectivity over TCP/IP in Arduino) 
2. PIR Sensor (for detecting presence of an intruder)  
3. RaspberryPi V2 Camera Module (for capturing footage in Raspberry Pi) 
4. DHT11 Temperature & Humidity sensor (for detecting excessive heat) 
5. HCSR04 Ultrasonic Sensor (for monitoring water level in tanks)
6. MQ2 Gas Sensor (for detecting methane and butane gas)

Whenever any of these sensors are triggered, the user will be immediately notified via email. This will be helpful in monitoring the home while the owner is away.
