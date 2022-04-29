#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>


long strToLong(char* str)
{
    char* endptr;
    errno = 0;
    long temp = strtol(str, &endptr, 10);
    if (errno)
    {
        perror("error");
        return -1;
    }
    if (strcmp(str, endptr) == 0 || strlen(endptr) != 0)
    {
        fprintf(stderr, "bad input");
        return -1;
    }
    return temp;
}

int main(int argc, char *argv[]) {
	
    if (argc < 3) {
	fprintf(stderr,"Wrong args\nusage: %s <file_name> <amount_of_output_strings>", argv[0]);
	return 1;
    }

    char *file_name = argv[1];
    
    long n  = strToLong(argv[2]);
    if( n == -1) return -1;
    else if (n < 1)
    {
        fprintf(stderr, "number of lines must be > 0");
        return -1;
    }
   
	FILE *file = fopen(file_name, "r");

	if (file==NULL) {
		fprintf(stderr,"Error: can't open file %s", argv[1]);
		return 1;
	}

	char symb;
	long printed = 0;
	while ((symb = fgetc(file))!=EOF) {
		if (symb=='\n')
			printed++;
		if (printed==n && n!=0) {
			getc(stdin);
			printed = 0;
		}

		putc(symb, stdout);
	}
	if (fclose(file)) {
		fprintf(stderr,"File %s can't be written", file_name);
		return 1;
	}
	return 0;
}
