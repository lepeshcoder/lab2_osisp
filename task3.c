#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[]) {

	if (argc < 3) {
		fprintf(stderr,"Wrong args\nusage: %s <file_name> <amount_of_output_strings>", argv[0]);
		return 1;
	}

	char *file_name = argv[1];

	
	char *ptr;
    	long n = strtol(argv[2], &ptr, 10);
    	if (n == LONG_MAX || n == LONG_MIN) {
        perror("Big number");
        return -1;
    }
    else if (n < 0) {
        fprintf(stderr, "Number less than 0");
        return -1;
    }
    else if (strcmp(argv[2], ptr) == 0 || strlen(ptr) != 0) {
        fprintf(stderr, "Error input: Not a number");
        return -1;
    }

	
	FILE *file = fopen(file_name, "r");

	if (file==NULL) {
		fprintf(stderr,"Error: can't open file %s", argv[1]);
		return 1;
	}

	char symb;
	int printed = 0;
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
