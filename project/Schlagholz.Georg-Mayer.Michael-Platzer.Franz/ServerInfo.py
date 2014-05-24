 #!/usr/bin/python3
# coding=UTF-8
class ServerInfo: 
    def getInfos(self):
      """returns hostname and temperature in celsius of the computer"""
      temp = int(open("/sys/class/thermal/thermal_zone0/temp", "r").read())/1000
      hostname = str(open("/etc/hostname", "r").read()).rstrip('\n')
      return (hostname,temp)
if __name__ == "__main__":
  si = ServerInfo()
  hostname,temp = si.getInfos()
  unit = " °C"
  print("Hostname: "+hostname+"\tTemperature: "+str(temp)+unit)