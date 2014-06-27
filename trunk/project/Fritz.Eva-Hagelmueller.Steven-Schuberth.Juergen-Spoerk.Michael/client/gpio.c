#include"gpio.h"

int activate_gpio(int gpio_nr)
{
	if(gpio_is_active(gpio_nr))
	{
		return 0;
	}
	
	fprintf(stderr, "gpio %d is not active. try to activate it.\n", gpio_nr);

	int fdgpio, fd_direction;
	char path_direction[50];
	char gpio_number_string[2];

	sprintf(gpio_number_string, "%d", gpio_nr);
	
	strcpy(path_direction, "/sys/class/gpio/gpio");
	strcat(path_direction, gpio_number_string);
	strcat(path_direction, "/direction");

	fdgpio = open("/sys/class/gpio/export", O_WRONLY);
	if (fdgpio == -1)
	{
		perror("could not open file ");
		return 1;
	}
	
	if(write(fdgpio, gpio_number_string, 2) == -1)
	{
		perror("could not write to file export: ");
		close(fdgpio);
		return 1;
	}
	
	close(fdgpio);
	
	// sleep 100ms because if not there would be an error with the file permissions.
	usleep(150000);

	fd_direction = open(path_direction, O_WRONLY);
	if( fd_direction == -1)
	{
		perror("could not open file 'direction': ");
		return 1;
	}

	if(write(fd_direction, "out", 3) == -1)
	{
		perror("could not write to file");
		close(fd_direction);
		return 1;
	}
	
	close(fd_direction);
	
	fprintf(stderr, "gpio %d is now activated.\n", gpio_nr);
	
	return 0;
}

int gpio_is_active(int gpio_nr)
{
	char gpio_number_string[8];
	char path_value[50];
	
	sprintf(gpio_number_string, "%d", gpio_nr);
	
	strcpy(path_value, "/sys/class/gpio/gpio");
	strcat(path_value, gpio_number_string);
	strcat(path_value, "/value");
	
	int fd = open(path_value, O_WRONLY);
	
	if( fd == -1)
	{
		return 0;
	}
	
	close(fd);	
	return 1;
}

int gpio_on(int gpio_nr)
{
	int fd;
	char gpio_number_string[8];
	char path_value[50];
	
	sprintf(gpio_number_string, "%d", gpio_nr);
	
	strcpy(path_value, "/sys/class/gpio/gpio");
	strcat(path_value, gpio_number_string);
	strcat(path_value, "/value");
	
	fd = open(path_value, O_WRONLY);
	if( fd == -1)
	{
		perror("could not open file 'value': ");
		return 1;
	}

	if(write(fd, "1", 1) == -1)
	{
		perror("could not write to file");
		close (fd);
		return 1;
	}
	
	close(fd);
	
	return 0;
}

int gpio_off(int gpio_nr)
{
	int fd;
	char gpio_number_string[8];
	char path_value[50];
	
	sprintf(gpio_number_string, "%d", gpio_nr);
	
	strcpy(path_value, "/sys/class/gpio/gpio");
	strcat(path_value, gpio_number_string);
	strcat(path_value, "/value");
	
	fd = open(path_value, O_WRONLY);
	if (fd == -1)
	{
		perror("could not open file");
		return 1;
	}

	if(write(fd, "0", 1) == -1)
	{
		perror("could not write to file");
		close(fd);
		return 1;
	}

	close(fd);
	
	return 0;
}
