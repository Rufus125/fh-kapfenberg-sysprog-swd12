#!/usr/bin/python3
# coding=UTF-8
# Author: Michael Mayer
# Teammembers:Georg Schlagholz, Franz Platzer, Michael Mayer
import os
import sys, re, urllib.request, datetime
import time

def call_server(server):
   response= urllib.request.urlopen('https://'+server).read().decode('utf8')
   response = response.split('\t')
   response[0] = response[0].replace("Hostname: ", "")
   response[1] = response[1].replace("Temperature: ", "")
   response[1] = response[1].strip()
   return response

def function():
  #get serverlist
  servers = ["192.168.178.89:4443", "192.168.178.93:4443"]
  children = []
  for server in servers:
    r, w = os.pipe() # these are file descriptors
    wpid = os.fork()
    if wpid==0:
      """wpid is 0 means We are in Child_process"""
      children.append(wpid)
      os.close(r)
      w = os.fdopen(w, 'w')
      entry = call_server(server)
      entry = str(entry)
      w.write(entry)
      w.close()
      os._exit(0)
    elif wpid > 0:
      os.close(w) # use os.close() to close a file descriptor
      r = os.fdopen(r) # turn r into a file object
      txt = r.read()
      print(txt)
      for child in children:
        #wait for finish, then output
        os.waitpid(child, 0)
        os._exit(0)
          
if __name__ == "__main__":
  function()
  #fork for each server
  #get results after specific time
  #output result