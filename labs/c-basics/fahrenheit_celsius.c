#include <stdio.h>

int main(int argc, char **argv)
{
    int fahr;
    int lower;
    int upper;
    int step;
    if (argc < 2) {
        printf("You need to send the number of grades to convert\n");
        printf("How to execute: ./fahrenheit_celsius.o  <number>\n");
        return 1;
    }
    if (argc == 2) {
	fahr = atoi(argv[1]);
    	printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }
    else if (argc == 4) {
	lower = atoi(argv[1]);
	upper = atoi(argv[2]);
	step = atoi(argv[3]);
    	for (fahr = lower; fahr <= upper; fahr = fahr + step)
		printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }
    return 0;
}
