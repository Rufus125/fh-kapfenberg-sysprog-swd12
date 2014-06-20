#!/usr/bin/env python

from Tkinter import *
from datetime import *
import os
import time
import sys
import pyglet
import smbus

class Wecker():
    ringOn = datetime.now() + timedelta(0, 60)

    def __init__(self):
        self.timeString = self.ringOn.time().__str__()[0:5]

    def increaseValue(self):
        print "\a"
        self.ringOn = self.ringOn + timedelta(0, 60)
        self.timeString =  self.ringOn.time().__str__()[0:5]
        labelString.set(self.timeString)
        print self.timeString

    def decreaseValue(self):
        print "\a"
        self.ringOn = self.ringOn - timedelta(0, 60)
        self.timeString =  self.ringOn.time().__str__()[0:5]
        labelString.set(self.timeString)
        print self.timeString

    def waitToTime(self):
        now = datetime.now()
        while now < self.ringOn:
            print now.__str__()
            now = datetime.now()
            time.sleep(1)

        os._exit(0)

    def initTimeListener(self):
            global master
            master.destroy()
            pid = os.fork()
            if pid == 0: #child
                self.waitToTime()
            else: #parent
                os.waitpid(pid, 0)
                self.playSound()

    def playSound(self):
        print "play sound"
        pid2 = os.fork()
        if pid2 == 0: #child
            self.waitForStandUp()
            os._exit(0)
        else: #parent
            music = pyglet.resource.media('Amsel.wav')
            player = music.play()
            player.eos_action = player.EOS_LOOP
            os.waitpid(pid2, 0)

    def waitForStandUp(self):
        I2C_ADDRESS = 0x20  #@Todo Change to right address
        bus = smbus.SMBus(1)

        #Set all ports in input mode
        bus.write_byte(I2C_ADDRESS,0xFF)

        #Read all the unput lines
        value=bus.read_byte(I2C_ADDRESS)
        while(value > (value-30)):
            value=bus.read_byte(I2C_ADDRESS)



wecker = Wecker()

master = Tk()
labelString = StringVar()
labelString.set(wecker.timeString)
upBtn = Button(master, text="UP", command=wecker.increaseValue)
upBtn.grid(row=0)

label = Label(master, textvariable=labelString)
label.grid(row=1)

downBtn = Button(master, text="Down", command=wecker.decreaseValue)
downBtn.grid(row=2)

startBtn = Button(master, text="Start", command=wecker.initTimeListener)
startBtn.grid(row=3)
master.mainloop()
