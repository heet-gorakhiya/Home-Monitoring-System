import time
import botbook_mcp3002 as mcp #

smokeLevel= 0

def readSmokeLevel():
    global smokeLevel
    smokeLevel= mcp.readAnalog()

def main():
    while True: #
        readSmokeLevel() #
        print ("Current smoke level is %i " % smokeLevel) #
        if smokeLevel > 120:
            print("Smoke detected")
        time.sleep(0.5) # s

if __name__ == "_main_" :
    main()