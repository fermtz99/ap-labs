//Fernando Martinez A01630401
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define REPORT_FILE "packages_report.txt"

void analizeLog(char *logFile, char *report);

struct Package {
    char name[30];
    char installDate[17];
    char lastUpdate[17];
    int updateTimes;
    char removalDate[17];
};

static int removedPackages = 0;
static int upgradedPackages = 0;

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./pacman-analizer.o pacman.log\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    char data[1000000];
    int arrayIndex = 0;
    struct Package packages[10000];
    int filedesc = open(logFile, O_RDONLY);
    if(filedesc < 0) {
        printf("File not found\n");
        return 1;
    }
    else {
        printf("File opened\n");
        int fileRead = read(filedesc, data, 10000000);
        if(fileRead < 0) {
            printf("File not read\n");
        }
        else {
            printf("Reading input file\n");
            char line[200];
            int i = 0;
            int k = 0;
            while(data[i] != '\0') {
                line[k] =  data[i];
                if(data[i] == '\n') {
                    char date[17];
                    int j;
                    for(j = 0; j < 16; j++) {
                        date[j] = line[j+2];
                    }
                    char *action;


                    action = strstr(line, "installed");
                    if(action != NULL) {
                        char name[30];
                        action +=10;
                        int o = 0;
                        while(action[o] != ' ') {
                            name[o] = action[o];
                            o++;
                        }

                        //Check if the program exists in the array
                        int p;
                        for(p = 0; p < arrayIndex; p++) {
                            if(strcmp(packages[p].name, name) != 0)
                                continue;
                            else
                               ;
                        }
                        if(p == arrayIndex) {
                            //new entry
                            strcpy(packages[arrayIndex].name, name);
                            strcpy(packages[arrayIndex].installDate, date);
                            strcpy(packages[arrayIndex].lastUpdate, date);
                            packages[arrayIndex].updateTimes = 0;
                            strcpy(packages[arrayIndex].removalDate, "-");
                            arrayIndex++;
                       }
                       int t;
                       for(t = 0; t < 100; t++){
                           name[t] = '\0';
                       }
                    }
                    else {



                        action = strstr(line, "upgraded");
                        if(action != NULL) {
                            //printf("UPGRADE\n");
                            char name[30];
                            action += 9;
                            int o = 0;
                            while(action[o] != ' ') {
                                name[o] = action[o];
                                o++;
                            }
                            int p;
                            for(p = 0; p < arrayIndex; p++) {
                                if(strcmp(packages[p].name, name) == 0) {
                                    if(packages[p].updateTimes == 1)
                                        upgradedPackages++;
                                    strcpy(packages[p].lastUpdate, date);
                                    packages[p].updateTimes++;
                                    p = arrayIndex;
                                }
                            }
                            int t;
                            for(t = 0; t < 100; t++){
                                name[t] = '\0';
                            }
                        }
                        else {



                            action = strstr(line, "removed");
                            if(action != NULL) {
                                //printf("REMOVED");
                                char name[30];
                                action += 8;
                                int o = 0;
                                while(action[o] != ' ') {
                                    name[o] = action[o];
                                    o++;
                                }
                                int p;
                                for(p = 0; p < arrayIndex; p++) {
                                    if(strcmp(packages[p].name, name) == 0) {
                                        removedPackages++;
                                        strcpy(packages[p].removalDate, date);
                                        p = arrayIndex;
                                    }
                                }

                                int t;
                                for(t = 0; t < 100; t++){
                                    name[t] = '\0';
                                }
                            }
                        }
                    }
                    int m;
                    for(m = 0; m <400; m++)
                        line[m] = ' ';
                    k = 0;
                }
                i++;
                k++;
            }
        }

        if(close(filedesc) < 0) {
            printf("File not closed");
            return 1;
        }
    }

    char finalData[10000];
    strcat(finalData, "\nPacman Packages Report\n");
    strcat(finalData, "----------------------\n");
    char dataBuffer[120];
    int currentInstalled = arrayIndex - removedPackages;
    sprintf(dataBuffer, "- Installed packages : %d\n- Removed packages   : %d\n- Upgraded packages  : %d\n- Current installed  : %d\n\n", arrayIndex, removedPackages, upgradedPackages, currentInstalled);
    strcat(finalData, dataBuffer);
    strcat(finalData, "List of packages\n");
    strcat(finalData, "----------------\n");
    char dataBuffer2[300];
    //printf("indexArray %d\n", arrayIndex);
    int h;
    for(h = 0; h < arrayIndex; h++) {
        sprintf(dataBuffer2, "- Package name        : %s\n  - Install date      : %s\n  - Last update date  : %s\n  - How many updates  : %d\n  - Removal date      : %s\n", packages[h].name, packages[h].installDate, packages[h].lastUpdate, packages[h].updateTimes, packages[h].removalDate);
        strcat(finalData, dataBuffer2);
    }
    //printf("%s\n", finalData);

    //printf("Report is generated at: [%s]\n", report);
    int filedesc2 = open(report, O_CREAT | O_WRONLY, 10000);
    if(filedesc2 < 0) {
        printf("File not found\n");
        return 1;
    }
    else {
        printf("File output opened\n");
        int fileWrite = write(filedesc2, finalData, 10000000);
        if(fileWrite < 0) {
            printf("File not written");
        }
        else
            printf("Output file written\n");
        if(close(filedesc2) < 0) {
            printf("File not closed");
            return 1;
        }

    }

}
