#include"binary_temp.h"

int set_leds( int temp )
{
	struct led{
		int value;
		int gpio_nr;
	};
		
	int value = temp;
	int i = NUMBER_OF_LEDS - 1;
	
	struct led leds[NUMBER_OF_LEDS];
	
	leds[0].value = 1;
	leds[0].gpio_nr = 17;
	
	leds[1].value = 2;
	leds[1].gpio_nr = 22;
	
	leds[2].value = 4;
	leds[2].gpio_nr = 23;	
	
	leds[3].value = 8;
	leds[3].gpio_nr = 24;

	leds[4].value = 16;
	leds[4].gpio_nr = 25;

	leds[5].value = 32;
	leds[5].gpio_nr = 27;
	
	activate_gpio(18);
	activate_gpio(4);
	
	if(value < 0)
	{
		gpio_off(18);
		gpio_on(4);
		value = value * (-1);
	}
	else if(value > 0)
	{
		gpio_off(4);
		gpio_on(18);	
	}
	else
	{
		gpio_off(4);
		gpio_off(18);
	}
	
	for(; i >= 0; i--)
	{
		activate_gpio(leds[i].gpio_nr);
		gpio_off(leds[i].gpio_nr);
		if( leds[i].value <= value )
		{
			value -= leds[i].value;
			gpio_on(leds[i].gpio_nr);
		}
	}
	
	return 0;
}
