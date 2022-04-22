#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if (argc < 3){
		fprintf(stderr,"Wrong input!\nusage: %s <src_file> <dist_file>", argv[0]);
		return 1;
	}

	FILE* file_1 = fopen(argv[1], "r");

	if (file_1 == NULL){
		fprintf(stderr,"File %s can't be opened", argv[1]);
		return 1;
	}

	FILE* file_2 = fopen(argv[2], "w");

	if (file_2 == NULL){
		fprintf(stderr,"File %s can't be opened", argv[2]);
		return 1;
	}


	char symb;
	while ((symb = fgetc(file_1)) != EOF){
		fputc(symb, file_2);
	}

	struct stat bufstat;
	if ( stat( argv[1], &bufstat ) )
	{
		fputs("Cant read file stats!\n", stderr);
		return -1;
	}
	
	if ( chmod( argv[2], bufstat.st_mode ) )
	{
		fputs("Cant set file stats!\n", stderr);
		return -1;
	}

	if (fclose(file_1)) {
		fprintf(stderr,"File %s can't be written", argv[1]);
		return 1;
	}
	if (fclose(file_2)) {
		fprintf(stderr,"File %s can't be written", argv[2]);
		return 1;
	}
}
