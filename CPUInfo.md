## Parent ##
[ThirdProject](ThirdProject.md)
# Introduction #

The application gets CPU infos like processor type and temperature
and serves it via network.
The client has a list of servers with their IP-Adresses and asks them parallel for their CPU temperature and outputs the servername and temperature to stdout.

# Details #

see: cat /sys/class/thermal/thermal\_zone0/temp

see: cat /proc/cpuinfo
see: cat /etc/hostname