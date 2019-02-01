import webbrowser
import keyboard
import codecs
import urllib
import time #import time for creating delay 
import Adafruit_CharLCD as LCD #Import LCD library 
import Adafruit_DHT #Import DHT Library for sensor

#urllib.request.get('169.254.70.71')

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

lcd.message('DHT11 with Pi') #Give a intro message

time.sleep(2) #wait for 2 secs
f=open("temp.html",'w')

while 1: #Infinite Loop
    
    humidity, temperature = Adafruit_DHT.read_retry(sensor_name, sensor_pin) #read from sensor and save respective values in temperature and humidity varibale  
    lcd.clear() #Clear the LCD screen
    lcd.message ('Temp = %.1f C' % temperature) # Display the value of temperature
    lcd.message ('\nHum = %.1f %%' % humidity)  #Display the value of Humidity 
    chodu = "<html><head><title>Raspberry Pi</title></head><body><h1>Humidity: "+str(int(humidity))+"</h1><h1>Temperature: "+str(temperature)+"</h1></body></html>"
    #f=open("temp.html",'w')
    f.write(chodu)
    webbrowser.open("temp.html")
    keyboard.press_and_release('ctrl+shift+tab, ctrl+w')
    time.sleep(2) #Wait for 2 sec then update the values
    #webbrowser.close("temp.html")