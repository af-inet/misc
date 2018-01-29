#include <stdlib.h>
#include <stdio.h>

// beware, error checking is ommitted for clarity
char *readfile(char *filename){
	FILE *f;
	char *buf;
	long size;

	if( !(f=fopen(filename, "r")) )
		return NULL;
	
	fseek(f, 0L, SEEK_END);	
	
	size = ftell(f);
	
	fseek(f, 0L, SEEK_SET);	
	
	buf = malloc(size+1);
	
	fread(buf, 1, size, f);
	
	buf[size] = 0;

	fclose(f);

	return buf;
}
