// Fernando Martinez
// A01630401

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void copyToFile(char *origin, char *target, int flagInput, int flagOutput) {
	char data[BUFSIZ];

	// Just write to stdout from stdin
	if(flagInput == 1) {
		do {
			int lenRead = read(0, data, 512);
			//data[lenRead] = '\0';
			write(1, data, lenRead);
		} while(getchar() != EOF);
	}
	else {
		int fileDescOrigin = open(origin, O_RDONLY);
		if(fileDescOrigin < 0)
			printf("Origin file not found\n");
		else {
			int originRead = read(fileDescOrigin, data, 1000000);
			if(originRead < 0)
				printf("File not read\n");
			else
				close(fileDescOrigin);

			// Write from file to stdout
			if(flagOutput == 1) {
				write(1, data, originRead);
			}
			else {
				// Write from file to another file creating it
				int fileDescTarget = open(target, O_CREAT | O_WRONLY, S_IROTH | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
				if(fileDescTarget < 0)
					printf("Target file not opened\n");
				else {
					int fileWrite = write(fileDescTarget, data, originRead);
					if(fileWrite < 0)
						printf("File not written\n");
					else
						close(fileDescTarget);
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	// Write from stdin to stdout
	if(argc == 1)
		copyToFile("nothing", "nothing", 1, 1);
	// Write from file to stdout
	else if(argc == 2)
		copyToFile(argv[1], "nothing", 0, 1);
	// Write from file to another file
	else if(argc == 3)
		copyToFile(argv[1], argv[2], 0, 0);
}
