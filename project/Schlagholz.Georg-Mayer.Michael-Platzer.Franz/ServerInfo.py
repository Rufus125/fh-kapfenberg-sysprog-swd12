#!/usr/bin/python3
# coding=UTF-8
# Author: Franz Platzer
# Teammembers:Georg Schlagholz, Franz Platzer, Michael Mayer 
import os

class ServerInfo:
    def getInfos(self):
      """returns hostname and temperature in celsius of the computer as a tuple"""
      p = '/sys/class/thermal/thermal_zone0/temp'
      if not os.path.isfile(p):
        p = '/sys/bus/platform/devices/coretemp.0/temp1_input'
        if not os.path.isfile(p):
          p = '/sys/class/hwmon/hwmon2/temp1_input'
          if not os.path.isfile(p):
            p = '/sys/class/hwmon/hwmon1/temp1_input'
            if not os.path.isfile(p):
              p = '/sys/class/hwmon/hwmon0/temp1_input'
              if not os.path.isfile(p):
                p = '/sys/class/thermal/thermal_zone1/temp'
                if not os.path.isfile(p):
                  p = '/sys/class/thermal/thermal_zone3/temp'
      if os.path.isfile(p):
        temp = int(open(p, "r").read()) #get temp
        temp /= 1000 #because value is in minicelsius
        hostname = str(open("/etc/hostname", "r").read()).rstrip('\n') #get hostname
        return (hostname,temp)
      else:
        raise Exception("Couldn't find temp files")

if __name__ == "__main__":
  si = ServerInfo()
  hostname,temp = si.getInfos()
  unit = " °C"
  print("Hostname: "+hostname+"\tTemperature: "+str(temp)+unit)