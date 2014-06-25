#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include "tft.h"
#include "RAIO8870.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringSerial.h>

char device[] = "/dev/ttyACM0"; // Arduino Uno

int fd;
unsigned long baud = 9600;

int main(void);
void loop(void);
void setup(void);

char lastStateRed[4] = "";
char lastStateGreen[4] = ""; 

void setup() {
    printf("%s \n", "Raspberry Startup!");
    fflush(stdout);

    /************* Setup Serial connection **********/
    // get filedescriptor
    if ((fd = serialOpen(device, baud)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        exit(1);
    }

    // setup GPIO in wiringPi mode
    if (wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
        exit(1);
    }

    /************* Setup Display ********************/
    if (!bcm2835_init()) {
        fprintf(stdout, "Unable to start bcm2835: %s\n", strerror(errno));
        exit(1);
    }

    TFT_init_board();
	TFT_hard_reset();
	RAIO_init();
}

void loop() {
    // read signal
    if (serialDataAvail(fd)) {
        unsigned char str[3] = "";

        for (int i = 0; i < fd; i++) {
            char c = serialGetchar(fd);
            str[i] = c;
        }

        char output[35] = "Lampe Rot: ";

        if (str[1] == '2') {
            printf("Red (%C%C): %C\n", str[0], str[1], str[2]);
	    
	    if (str[2] == '0') {
	    	strcat(output, "Aus");
		strcpy(lastStateRed, "Aus");
            }
	    else {
		strcat(output, "Ein");
		strcpy(lastStateRed, "Ein");
	    }

	    strcat(output, " || Lampe Gelb: ");
	    strcat(output, lastStateGreen);
        }
        else if (str[1] == '3') {
            printf("Yellow (%C%C): %C\n", str[0], str[1], str[2]);

	    strcat(output, lastStateRed);
	    strcat(output, " || Lampe Gelb: ");

	    if (str[2] == '0') {
	    	strcat(output, "Aus");
		strcpy(lastStateGreen, "Aus");
            }
	    else {
		strcat(output, "Ein");
		strcpy(lastStateGreen, "Ein");
	    }

	    
        }

        fflush(stdout);

        //printf("%s", str);
        RAIO_SetFontSizeFactor(0);
        RAIO_print_text(10, 10, output, COLOR_WHITE, COLOR_BLACK);
    }
}

int main() {
    setup();
    while(1) loop();
    return(0);
}
