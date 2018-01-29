#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <ftw.h>

static int display_info(
	const char *fpath,
	const struct stat *sb,
	int tflag,
	struct FTW *ftwbuf ){

	int isdir, level, size, base;

	level = ftwbuf->level;
	size  = sb->st_size;
	base  = ftwbuf->base;
	isdir = sb->st_mode & S_IFDIR;

	printf("%d %-6d %-16s %d %-12s %s\n",
		level, size, fpath, base, fpath + base, isdir ? "dir" : "file");

	return 0;
}

int main(int argc, char *argv[]){
	
	if( nftw(".", display_info, 0, 0) == -1 )
		perror("nftw");

	return 0;
}

