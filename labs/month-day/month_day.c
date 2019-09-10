#include <stdio.h>

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char *name[] = {
    "Illegal month", "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October" ,"November", "December"
};

int main(int argc, char **argv) {
    char *month;
    int pmonth = 12;
    int pday = 30;
    if(argc >= 3) {
        int year = atoi(argv[1]);
        int yearday = atoi(argv[2]);
        month_day(year, yearday, &pmonth, &pday);
        month = (pmonth < 1 || pmonth > 12) ? name[0] : name[pmonth];
        printf("%s %d, %d\n", month, pday, year);
        return 0;
    }
    else {
        printf("You need to send the year and the day of the year\n");
        printf("How to execute: ./month_day <year> <day of the year>\n");
        return 1;
    }
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i;
	int leap;
	leap = year%4 == 0 && year%100 !=0 || year%400 == 0;
	for(i = 0; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
