#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE_G 10

int index_tail_buffer(const char *buffer, int bufsize, int ntail, int *nlines){
	
	int i;
	i=0;
	while(i < bufsize && *nlines <= ntail)
	{
		if(*(buffer + bufsize - i - 1) == '\n')
		{
			(*nlines)++;
		}
		i++;
	}
	if(*nlines<=ntail)
	{
		return -1;
	}
	return(bufsize-i);
}

void tail_before_pos(int fd, unsigned int pos, int ntail){

	int nlines;
	int c;
	int i;
	int readsize;
	char buffer[BUFSIZE_G];

	nlines = 0;
	lseek(fd, pos - BUFSIZE_G, SEEK_SET);
	readsize = read(fd, buffer, BUFSIZE_G);
	
	if (readsize == 0)
	{
		lseek(fd, 0, SEEK_SET);
		read(fd, buffer, pos);
		for (i = 0; i < pos; i++)
		{
			printf("%c", *(buffer + i));
		}
		return;
	}
	
	if ((c = index_tail_buffer(buffer, readsize, ntail, &nlines)) < 0)
	{
		tail_before_pos(fd, pos - readsize, ntail - nlines);
		for (i = 0; i < readsize; i++)
		{
			printf("%c", *(buffer + i));
		}

	}
	else
	{
		for (i = c; i < readsize; i++)
		{
			printf("%c", *(buffer + i));
		}
	}
}

void tail(const char *path, int ntail){

	int fd;
	unsigned int pos;

	fd = open(path, O_RDONLY);
	pos = lseek(fd, 0, SEEK_END);

	tail_before_pos(fd, pos, ntail);
}

int main(int argc, char *argv[]){

	int arg;
	int c;

	while((c = getopt(argc, argv, "n:")) != -1){

    switch(c){

      case 'n':

        arg = atoi(optarg);

        tail(argv[1], arg);

        break;
    }
  }
	
	return 0;
}
