#!/usr/bin/python3
# Author: Michael Mayer
# Teammembers:Georg Schlagholz, Franz Platzer, Michael Mayer
import os

def call_server(server):
    pass

def function():
  #get serverlist
  servers = []
  chidren = []
  r, w = os.pipe() # these are file descriptors
  for server in servers:
    wpid = os.fork()
    if wpid==0:
      """wpid is 0 means We are in Child_process"""
      children.append(wpid)
      call_server(server)
      os.close(r)
      w = os.fdopen(w, 'w')
      print "child: writing"
      w.write("here's some text from the child")
      w.close()
      os._exit(0)
    elif wpid > 0:
      os.close(w) # use os.close() to close a file descriptor
      r = os.fdopen(r) # turn r into a file object
      print "parent: reading"
      txt = r.read()
      for child in children:
        #wait for finish, then output
        os.waitpid(child, 0)
          
if __name__ == "__main__":
  function()
  #fork for each server
  #get results after specific time
  #output result