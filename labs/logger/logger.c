#include <stdio.h>
#include <signal.h>
#include <stdarg.h>

#define RESET		0
#define BRIGHT 		1
#define DIM		2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

void textcolor(int attr, int fg, int bg)
{	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

char *convert(unsigned int num, int base) {
	static char Representation[] = "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = Representation[num%base];
		num /= base;
	} while (num != 0);

	return(ptr);
}

int infof(const char *format, ...) {
	// Color of the text
	textcolor(RESET, WHITE, BLACK);

	const char *traverse;
	int i;
	char *s;
	//char fmtbuf[256];

	va_list arg;
	va_start(arg, format);

	for(traverse = format; *traverse != '\0'; traverse++) {
		if(*traverse != '%') {
			putchar(*traverse);
			continue;
		}
		/*while(*traverse != '%' && *traverse != '\0') {
			putchar(*traverse);
			continue;
		}*/
		//traverse++;

		switch(*++traverse) {
			case 'c':
				i = va_arg(arg, int);
				putchar(i);
				break;
			case 'd':
				i = va_arg(arg, int);
				if(i < 0) {
					i = -i;
					putchar('-');
				}
				puts(convert(i, 10));
				break;
			case 'o':
				i = va_arg(arg, unsigned int);
				puts(convert(i, 8));
				break;
			case 's':
				s = va_arg(arg, char *);
				puts(s);
				break;
			case 'x':
				i = va_arg(arg, unsigned int);
				puts(convert(i, 16));
				break;
		}
	}
	va_end(arg);
	//printf("%s", format);
	return 0;
}

int warnf(const char *format, ...) {
	// Warning text color
	textcolor(RESET, YELLOW, BLACK);

	const char *traverse;
        int i;
        char *s;

        va_list arg;
        va_start(arg, format);

        for(traverse = format; *traverse != '\0'; traverse++) {
		if(*traverse != '%') {
                        putchar(*traverse);
                        continue;
                }

                /*while(*traverse != '%' && *traverse != '\0') {
                        putchar(*traverse);
                        traverse++;
                }
                traverse++;*/

                switch(*++traverse) {
                        case 'c':
                                i = va_arg(arg, int);
                                putchar(i);
                                break;
                        case 'd':
                                i = va_arg(arg, int);
                                if(i < 0) {
                                        i = -i;
                                        putchar('-');
                                }
                                puts(convert(i, 10));
                                break;
                        case 'o':
                                i = va_arg(arg, unsigned int);
                                puts(convert(i, 8));
                                break;
                        case 's':
                                s = va_arg(arg, char *);
                                puts(s);
                                break;
                        case 'x':
                                i = va_arg(arg, unsigned int);
                                puts(convert(i, 16));
				break;
                }
        }
        va_end(arg);
	//printf("%s", format);
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int errorf(const char *format, ...) {
	// Error text color
	textcolor(BRIGHT, RED, BLACK);

	const char *traverse;
        int i;
        char *s;

        va_list arg;
        va_start(arg, format);

        for(traverse = format; *traverse != '\0'; traverse++) {
		if(*traverse != '%') {
                        putchar(*traverse);
                        continue;
                }

                /*while(*traverse != '%' && *traverse != '\0') {
                        putchar(*traverse);
                        traverse++;
                }
                traverse++;*/

                switch(*++traverse) {
                        case 'c':
                                i = va_arg(arg, int);
                                putchar(i);
                                break;
                        case 'd':
                                i = va_arg(arg, int);
                                if(i < 0) {
                                        i = -i;
                                        putchar('-');
                                }
                                puts(convert(i, 10));
                                break;
                        case 'o':
                                i = va_arg(arg, unsigned int);
                                puts(convert(i, 8));
                                break;
                        case 's':
                                s = va_arg(arg, char *);
                                puts(s);
                                break;
                        case 'x':
                                i = va_arg(arg, unsigned int);
                                puts(convert(i, 16));
                                break;
                }
        }
        va_end(arg);

        //printf("%s", format);
        textcolor(RESET, WHITE, BLACK);
        return 0;
}

int panicf(const char *format, ...) {
	// Normal text color
        textcolor(RESET, WHITE, BLACK);

	const char *traverse;
        int i;
        char *s;

        va_list arg;
        va_start(arg, format);

        for(traverse = format; *traverse != '\0'; traverse++) {
		if(*traverse != '%') {
                        putchar(*traverse);
                        continue;
                }
               /* while(*traverse != '%' && *traverse != '\0') {
                        putchar(*traverse);
                        traverse++;
                }
                traverse++;*/

                switch(*++traverse) {
                        case 'c':
                                i = va_arg(arg, int);
                                putchar(i);
                                break;
                        case 'd':
                                i = va_arg(arg, int);
                                if(i < 0) {
                                        i = -i;
                                        putchar('-');
                                }
                                puts(convert(i, 10));
                                break;
                        case 'o':
                                i = va_arg(arg, unsigned int);
                                puts(convert(i, 8));
                                break;
                        case 's':
                                s = va_arg(arg, char *);
                                puts(s);
                                break;
                        case 'x':
                                i = va_arg(arg, unsigned int);
                                puts(convert(i, 16));
                                break;
                }
        }
        va_end(arg);

        //printf("%s", format);
	raise(SIGABRT);
        return -1;
}

