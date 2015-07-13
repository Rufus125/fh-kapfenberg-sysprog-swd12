Siri2Pi (Home Automation)

Team: Daniel Hösele - Daniel Frech - 17.05.2014

# Introduction #

Run custom python code on a raspi with voice commands using Siri-API.

Siri-API is a tool which opens Siri for your own wishes WITHOUT the requirement of a Jailbreak. Basically it is like GoogolPlex but it is much more flexible since you can host it on your own computer. You just say Google and your keyword, by default "Siri" and everything what you say after your keyword will be redirected to the API. Of course, using Google without the keyword is still possible.

You need a Linux running computer (tested on Raspberry Pi) and a Squid Proxy version compiled with SSL support. These versions aren't available from official package sources, so you have to compile it by yourself. You can follow the instructions in the documentation.
https://github.com/HcDevel/Siri-API

# Details #

Hardware:
2 Raspberry Pi (both on Raspbian), 1 Ninja Blocks, several Sensors and Actuators

Software:
Siri-API, Squid Proxy, Python3

# Progress #

Siri-API is set up and running.

Custom Python-Code can be placed in the commands.py
(<a href='https://www.dropbox.com/sh/55my4fng760r4mf/AADJhhRVreorhhOob8xQSzIoa/SS2014/SysProg/ex3/commands.py'>link</a>)


**--Snip--Snap--Snip--**

Voice Command: "Google Siri Server"

I have another pi running as a webserver.
A cronjob is set up to call autoscript.sh (<a href='https://www.dropbox.com/sh/55my4fng760r4mf/AABMDvZiju7J3yX35SS-Ob5Ya/SS2014/SysProg/ex3/autoscript.sh'>link</a>) every 60 sec to save data regarding the system (cpu usuage, mem, clockrate ...) into seperate files.
The python-function which is called from Siri-API reads this data and presents it well formatted to the user.

https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AAALNzuoTjTj8830fwq7tS2-a/SS2014/SysProg/ex3/thumbnails/1.png?token_hash=AAEGT990IOuh6Z_J7XjHc62KMOETg1BBfqh8pchGuoO7xA&expiry=1400344470
https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AAAznjFL9j9jacsWLr7U7N3Aa/SS2014/SysProg/ex3/thumbnails/2.png?token_hash=AAEGT990IOuh6Z_J7XjHc62KMOETg1BBfqh8pchGuoO7xA&expiry=1400344470

**--Snip--Snap--Snip--**

Voice Command: "Google Siri Wohnung"

As I have a NinjaBlocks (http://ninjablocks.com/collections/ninja-blocks) set up in my apartment, I can easily gather data from its sensors and even actuate remote control outlets (Funksteckdosen).
The second script presents the current temperature and humidity of my bedroom to the user.

https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AABOkUly_HZEUmkJJgSvAcmRa/SS2014/SysProg/ex3/thumbnails/3.png?token_hash=AAEGT990IOuh6Z_J7XjHc62KMOETg1BBfqh8pchGuoO7xA&expiry=1400344470
https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AAD-DoxESC4ZUlrvrfVGPuuSa/SS2014/SysProg/ex3/thumbnails/4.png?token_hash=AAEGT990IOuh6Z_J7XjHc62KMOETg1BBfqh8pchGuoO7xA&expiry=1400344470

**--Snip--Snap--Snip--**

Voice Command: "Google Siri Licht an"

It triggers the remote control outlet of the LEDs behind my TV.
This actually happens over a "webhook" which triggers a rule to send an 433MHz Hex-Code to the outlet.

https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AAALAyzTOZmSdpBZ2Roov_tla/SS2014/SysProg/ex3/thumbnails/5.png?token_hash=AAEGT990IOuh6Z_J7XjHc62KMOETg1BBfqh8pchGuoO7xA&expiry=1400344470
https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AADfY7Ikq0k5RYgVubFuOFyBa/SS2014/SysProg/ex3/thumbnails/6.png?token_hash=AAEGT990IOuh6Z_J7XjHc62KMOETg1BBfqh8pchGuoO7xA&expiry=1400344470

**--Snip--Snap--Snip--**

Voice Command: "Google Siri Computer an"

This command uses the os.system-function of python and calls the console-program "wakeonlan" with the mac-address of my pc.

https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AAADsw2EYXR-vCnMMGKrSs66a/SS2014/SysProg/ex3/thumbnails/7.png?token_hash=AAHpopqzOFrNZ2-5VLKc8wyXFACl-sNTnxj007jYDYqW-Q&expiry=1400346293
https://dl.dropboxusercontent.com/sh/55my4fng760r4mf/AAB0hitueqL_K1r3gj2IyKcda/SS2014/SysProg/ex3/thumbnails/8.png?token_hash=AAHpopqzOFrNZ2-5VLKc8wyXFACl-sNTnxj007jYDYqW-Q&expiry=1400346293

FullRes-Screenshots:
https://www.dropbox.com/sh/55my4fng760r4mf/AABf98OkhpHf7BxQejAac1lxa/SS2014/SysProg/ex3