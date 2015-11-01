#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int alignment = 0;
int compress = 0;
int width = 72;
char *ptr;
int main (int argc, char *argv[]){
int i =1;
while (i < argc){
	//printf("argument is: %s\ni=%d", argv[i],i);
	if (!strcmp(argv[i] , "-w")){
	    //width flag
	    i++;
	    //printf("width start\n");
	    width = atoi(argv[i]);
	    i++;
	    //printf("width end - %d", width);
	    }
	
	else if (!strcmp(argv[i] , "-r")){
	    //right alignment
	    alignment = 1;
	    i++;
	    //printf("right\nalignment=%d", alignment);
	}
	else if (!strcmp(argv[i] , "-j")){
	    //justified
	    alignment = 2;
	    i++;
	    //printf("justified\nalignment=%d", alignment);
	}
	else if (!strcmp(argv[i] , "-s")){
	    //compress spaces
	    compress = 1;
	    i++;
	    //printf("compress");
	}
	else if ((!strcmp(argv[i] , "-h")) || (!strcmp(argv[i] , "-?"))){
	    printf("Usage message**");
	    return 0;
	    //print usage message and exit program
	}
	
    }
}
