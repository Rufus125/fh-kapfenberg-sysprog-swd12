#include "network.h"

int main(int argc, char *argv[])
{
	int temp = 0;
	
	if(argc == 2)
	{	
		if (sscanf (argv[1], "%i", &temp)!=1) 
		{ 
			fprintf (stderr, "error - not an integer\n"); 
			exit(1);
		}
		
		set_leds( temp );
	}
	else
	{
		while(get_temp("10.52.201.47", &temp) != 1)
		{
			printf("temp: %d\n", temp);
			set_leds( temp );
			sleep(1);
		}
	}
		
	return 0;
}
