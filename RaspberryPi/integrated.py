import RPi.GPIO as GPIO
import time
import os
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
import webbrowser
import codecs
import urllib
import time #import time for creating delay 
import Adafruit_CharLCD as LCD #Import LCD library 
import Adafruit_DHT #Import DHT Library for sensor

#urllib.request.get('169.254.70.71')
def SendMail(ImgFileName):
    img_data = open(ImgFileName, 'rb').read()
    msg = MIMEMultipart()
    msg['Subject'] = 'Intruder'
    msg['From'] = 'tempt919@gmail.com'
    msg['To'] = 'neelsshuklaa@gmail.com'

    text = MIMEText("test")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(ImgFileName))
    msg.attach(image)

    s = smtplib.SMTP('smtp.gmail.com', 587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login("tempt919@gmail.com","qazwsxedcrfv123456")
    s.sendmail("tempt919@gmail.com", "neelsshuklaa@gmail.com", msg.as_string())
    s.quit()

TRIG = 23 
ECHO = 24
GPIO.setmode(GPIO.BCM)
GPIO.setup(26, GPIO.IN)
GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)


sensor_name = Adafruit_DHT.DHT11 #we are using the DHT11 sensor
sensor_pin = 17 #The sensor is connected to GPIO17 on Pi

lcd_rs        = 7  #RS of LCD is connected to GPIO 7 on PI
lcd_en        = 8  #EN of LCD is connected to GPIO 8 on PI 
lcd_d4        = 25 #D4 of LCD is connected to GPIO 25 on PI
lcd_d5        = 24 #D5 of LCD is connected to GPIO 24 on PI
lcd_d6        = 23 #D6 of LCD is connected to GPIO 23 on PI
lcd_d7        = 18 #D7 of LCD is connected to GPIO 18 on PI
lcd_backlight =  0  #LED is not connected so we assign to 0

lcd_columns = 16 #for 16*2 LCD
lcd_rows    = 2 #for 16*2 LCD

lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7, 
                           lcd_columns, lcd_rows, lcd_backlight)   #Send all the pin details to library 

lcd.message('DHT11 with Pi \n -CircuitDigest') #Give a intro message

time.sleep(2) #wait for 2 secs

while 1: #Infinite Loop
    time.sleep(2)
    humidity, temperature = Adafruit_DHT.read_retry(sensor_name, sensor_pin) #read from sensor and save respective values in temperature and humidity varibale  
    lcd.clear() #Clear the LCD screen
    lcd.message ('Temp = %.1f C' % temperature) # Display the value of temperature
    lcd.message ('\nHum = %.1f %%' % humidity)  #Display the value of Humidity 
    #update = "<html><head><title>Raspberry Pi</title></head><body><h1>Humidity: "+str(int(humidity))+"</h1><h1>Temperature: "+str(temperature)+"</h1></body></html>"
    #f=open("temp.html",'w')
    #f.write(update)
    #webbrowser.open("temp.html")
    if GPIO.input(26):
        #GPIO.output(24, True)
        #time.sleep(0.5) #Buzzer turns on for 0.5 sec
        #GPIO.output(24, False)
        print("Motion Detected...")
        
        time.sleep(5) #to avoid multiple detection
    else:
        print("No motion")
    #time.sleep(2) #Wait for 2 sec then update the values

    GPIO.output(TRIG, False)
    print ("Waiting For Sensor To Settle")
    time.sleep(2)
    #print("Hello1")
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)
    #print("Hello2")
    while GPIO.input(ECHO)==0:
        #print("Hello3")
        pulse_start = time.time()

    while GPIO.input(ECHO)==1:
        #print("Hello4")
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start

    distance = pulse_duration * 17150

    distance = round(distance, 2)

    print ("Distance: "+str(distance)+" cm")