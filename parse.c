#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int alingment = 0;
int compress = 0;
int width = 72;

main (int argc, char *argv[]){
int i =1;
while (i < argc){
	printf("%s", argv[i]);
	if (!strcmp(argv[i] , "-w")){
	    //width flag
	    i++;
	    if isdigit(argv[i]){
		width = argv[i];
		i++;
	    }
	}
	else if (!strcmp(argv[i] , "-r")){
	    //right alignment
	    alignment = 1;
	    i++;
	}
	else if (!strcmp(argv[i] , "-j")){
	    //justified
	    alignment = 2;
	    i++;
	}
	else if (!strcmp(argv[i] , "-s")){
	    //compress spaces
	    compress = 1;
	    i++;
	}
	else if ((!strcmp(argv[i] , "-h")) || (!strcmp(argv[i] , "-?"))){
	    //print usage message and exit program
	}
	else {
	    //exit program. Case of no additional arguments is handled by while loop
	}
    }
}
