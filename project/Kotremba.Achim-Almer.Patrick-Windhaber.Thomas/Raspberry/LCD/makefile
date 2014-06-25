all: LCD

LCD: LCD.o tft.o RAIO8870.o
	gcc LCD.o tft.o RAIO8870.o -lwiringPi -lbcm2835 -lrt -lm -o LCD

tft.o: tft.c tft.h
	gcc -Os -c tft.c

LCD.o: LCD.c 
	gcc -std=c99 -Os -c LCD.c 
	
RAIO8870.o: RAIO8870.c RAIO8870.h
	gcc -Os -c RAIO8870.c

clean:
	rm -rf *o LCD

