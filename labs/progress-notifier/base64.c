// Fernando Martinez
// A01630401

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "logger.h"

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66

float progress;
size_t resultIndex;

static const unsigned char d[] = {
    66,66,66,66,66,66,66,66,66,66,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,62,66,66,66,63,52,53,
    54,55,56,57,58,59,60,61,66,66,66,65,66,66,66, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,66,66,66,66,66,66,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66
};

void handleSignal(int sig) {
	infof("Progress: %f%%", progress);
}

// Code from en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64
int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize) {
   const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   const uint8_t *data = (const uint8_t *)data_buf;
   resultIndex = 0;
   size_t x;
   uint32_t n = 0;
   int padCount = dataLength % 3;
   uint8_t n0, n1, n2, n3;

   /* increment over the length of the string, three characters at a time */
   for (x = 0; x < dataLength; x += 3) {
	progress = (float)(((float)x / (float)dataLength)*100);

      /* these three 8-bit (ASCII) characters become one 24-bit number */
      n = ((uint32_t)data[x]) << 16; //parenthesis needed, compiler depending on flags can do the shifting before conversion to uint32_t, resulting to 0

      if((x+1) < dataLength)
         n += ((uint32_t)data[x+1]) << 8;//parenthesis needed, compiler depending on flags can do the shifting before conversion to uint32_t, resulting to 0

      if((x+2) < dataLength)
         n += data[x+2];

      /* this 24-bit number gets separated into four 6-bit numbers */
      n0 = (uint8_t)(n >> 18) & 63;
      n1 = (uint8_t)(n >> 12) & 63;
      n2 = (uint8_t)(n >> 6) & 63;
      n3 = (uint8_t)n & 63;

      /*
       * if we have one byte available, then its encoding is spread
       * out over two characters
       */
      if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
      result[resultIndex++] = base64chars[n0];
      if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
      result[resultIndex++] = base64chars[n1];

      /*
       * if we have only two bytes available, then their encoding is
       * spread out over three chars
       */
      if((x+1) < dataLength) {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = base64chars[n2];
      }

      /*
       * if we have all three bytes available, then their encoding is spread
       * out over four characters
       */
      if((x+2) < dataLength) {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = base64chars[n3];
      }
   }

   /*
    * create and add padding that is required if we did not have a multiple of 3
    * number of characters available
    */
   if (padCount > 0) {
      for (; padCount < 3; padCount++) {
         if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
         result[resultIndex++] = '=';
      }
   }
   if(resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
   result[resultIndex] = '\0';
   return 0;   /* indicate success */
}

// Code from en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64
int base64decode (char *in, size_t inLen, unsigned char *out, size_t outLen) {
    char *end = in + inLen;
    char iter = 0;
    uint32_t buf = 0;
    size_t len = 0;

    while (in < end) {
	progress = (float)(((float)len / (float)inLen)*100);

        unsigned char c = d[*in++];

        switch (c) {
        case WHITESPACE: continue;   /* skip whitespace */
        case INVALID:   return 1;   /* invalid input, return error */
        case EQUALS:                 /* pad character, end of data */
            in = end;
            continue;
        default:
            buf = buf << 6 | c;
            iter++; // increment the number of iteration
            /* If the buffer is full, split it into bytes */
            if (iter == 4) {
                if ((len += 3) > outLen) return 1; /* buffer overflow */
                *(out++) = (buf >> 16) & 255;
                *(out++) = (buf >> 8) & 255;
                *(out++) = buf & 255;
                buf = 0; iter = 0;

            }
        }
    }

    if (iter == 3) {
        if ((len += 2) > outLen) return 1; /* buffer overflow */
        *(out++) = (buf >> 10) & 255;
        *(out++) = (buf >> 2) & 255;
    }
    else if (iter == 2) {
        if (++len > outLen) return 1; /* buffer overflow */
        *(out++) = (buf >> 4) & 255;
    }

    outLen = len; /* modify to reflect the actual output size */
    return 0;
}


int main(int argc, char** argv){
	if(signal(SIGINT, handleSignal) == SIG_ERR)
		errorf("Can't catch SIGINT\n");
	if(signal(SIGUSR1, handleSignal) == SIG_ERR)
                errorf("Can't catch SIGUSR1\n");
	if(argc == 3) {
		int fOpen = open(argv[2], O_RDONLY);
		if(fOpen < 0)
			errorf("File not found\n");
		else {
			char data[1000000];
			int fRead = read(fOpen, data, 1000000);
			data[fRead] = '\0';
			char finalData[(int)(fRead * 1.5)];
			if(fRead < 0)
				errorf("File not read\n");
			else {
				close(fOpen);
				if((strcmp(argv[1], "--encode")) == 0) {

					// Start encoding
					base64encode(data, fRead, finalData, (fRead * 1.5));
					int fileDescTarget = open("encoded.txt", O_CREAT | O_WRONLY, S_IROTH | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
					if(fileDescTarget < 0)
						errorf("Target file not opened\n");
					else {
						int fileWrite = write(fileDescTarget, finalData, resultIndex);
						if(fileWrite < 0)
							errorf("File not written\n");
						else
							close(fileDescTarget);
					}
				}
				else if((strcmp(argv[1], "--decode")) == 0) {
					infof("File yet to decode\n");
					int result = base64decode(data, fRead, finalData, sizeof(finalData));
					infof("result %d\n", result);
					int fileDescTarget = open("decoded.txt", O_CREAT | O_WRONLY, S_IROTH | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
                                        if(fileDescTarget < 0)
                                                errorf("Target file not opened\n");
                                        else {
                                                int fileWrite = write(fileDescTarget, finalData, sizeof(finalData));
                                                if(fileWrite < 0)
                                                        errorf("File not written\n");
                                                else
                                                        close(fileDescTarget);
                                        }

				}
				else
					warnf("Use '--encode' or '--decode' option\n");
			}
		}
	}
	else
		warnf("How to use: ./main --encode/--decode 'name of file'\n");
	// Place your magic here
	return 0;
}
