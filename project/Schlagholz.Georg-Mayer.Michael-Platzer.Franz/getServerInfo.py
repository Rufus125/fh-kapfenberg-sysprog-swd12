#!/usr/bin/python3
# coding=UTF-8
# Author: Michael Mayer
# Teammembers:Georg Schlagholz, Franz Platzer, Michael Mayer
import os, sys, signal
import urllib.request

def call_server(server):
    """ server: a URL to the server IP:Port
        returns one entry: a tuple: hostname (string) and temperature in celsius (string) xXX.X_°C
     """
    response = urllib.request.urlopen('https://' + server).read().decode('utf8')  #get response from server
    response = response.split('\t')  #split by tab
    response[0] = response[0].replace("Hostname: ", "")  # remove unuseful info
    response[1] = response[1].replace("Temperature: ", "")
    response[1] = response[1].strip()  #delete newline
    return response

def call_servers():
    """ Iterates over each item in servers array and gets the server info"""
    #get serverlist
    servers = ["192.168.0.13:4443"]
    children = []
    for server in servers:
        r, w = os.pipe()  # these are file descriptors
        wpid = os.fork()# If an error occurs OSError is raised.
        if wpid == 0:
            """wpid is 0 means We are in Child_process"""
            signal.alarm(2)
            os.close(r)  #close the read pipe
            w = os.fdopen(w, 'w')  # turn w into a file object
            entry = call_server(server)  #call server to get server infos
            entry = str(entry)  #convert to a str to be able to write it to pipe
            w.write(entry)  #write to pipe
            w.close()  #close pipe file descriptor
            os._exit(0)  #exit child process
        elif wpid > 0:
            children.append((wpid,r))
            os.close(w)  # use os.close() to close a file descriptor

    for child in children:
      pid, status = os.waitpid(child[0],0) #maybe save server IP too to say that it failed to connect to this one
      if status == 0:#not necessary if waitpid(PID,0) should be changed for error handling
        r = child[1]
        r = os.fdopen(r)  # turn r into a file object
        txt = r.read()  # read the input from child
        print(txt)
        os._exit(0)
      else:
        os._exit(1) #on error

if __name__ == "__main__":
    call_servers()