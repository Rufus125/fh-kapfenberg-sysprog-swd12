 #!/usr/bin/python3
# coding=UTF-8
# Author: Georg Schlagholz
# Teammembers:Georg Schlagholz, Franz Platzer, Michael Mayer 
class ServerInfo: 
    def getInfos(self):
      """returns hostname and temperature in celsius of the computer as a tuple"""
      temp = int(open("/sys/class/thermal/thermal_zone0/temp", "r").read()) #get temp
      temp /= 1000 #because value is in minicelsius
      hostname = str(open("/etc/hostname", "r").read()).rstrip('\n') #get hostname
      return (hostname,temp)
if __name__ == "__main__":
  si = ServerInfo()
  hostname,temp = si.getInfos()
  unit = " °C"
  print("Hostname: "+hostname+"\tTemperature: "+str(temp)+unit)