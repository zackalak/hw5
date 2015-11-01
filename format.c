#include <stdio.h>
#include <ctype.h>
#include <string.h>


//basic node struct in a linked list of words
struct wordnode {

    //array of chars to hold the word (we're told max length is 100)
    char word[ 100 ];
    
    //pointer to the next word
    struct wordnode *nextword;
    
    //length of the word, can't be properly iterated with current scanf()
    int length;
};

int width = 72;
int alignment = 0;
int compress = 0;
int i,j,k,l; //variables to be used in forloops

//main takes in the number of arguments (space-delimited) from cmdline
//argc is #args, argv is a pointer to a char array of each arg
//arg[0] is the program name
int main (int argc, char *argv[]) {
    
    //declare a root node
    struct wordnode rootnode;
    //last node in the list
    //pointer to root node
    struct wordnode *input = &rootnode;
    
    struct wordnode *endnode = input;
    //The block below handles arguments from the command line
    i =1;
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
    //endnode = &input;

    //infinite while, broken when we get EOF
    while (1) {

	//read a word into the array of the wordnode pointed to by input and test for EOF
	if ( scanf( "%s", &( input->word[ 0 ] ) ) != EOF ) { 
	    
	    //echo back the word we just read in, char by char 
	    //char *letter = &( input->word[ 0 ] );
	    //while ( *letter != '\0' ) {
	//	printf ("%c", *letter );
	//	letter++;
	  //  }
	    
	    //no EOF: there are more words, so we add on to the end of the list
	    //create a new wordnode,
	    struct wordnode next; 
	    //and then point the nextword pointer of our current node to it
	    input->nextword = &next;

	    //point input to it as well for the next iteration of the loop
	    input = &next;
	    
	    //if there is a newline character!!
	    scanf("%1[/n]", &(input->word[0]));
	    input->nextword = &next;
	    input = &next;
	}
	else break;
    }
    *endnode = *input;
    if (alignment){
	if (alignment > 1){
	    //justified
	    
	}
	else{
	    //right aligned
	}
    }
    else{
	printf("left aligned");
	//left aligned
	input = &rootnode;
	j = 0;
	while(1) {
	    j += input->length;
	    char *let = &(input->word[0]);
	    if (j <= width) {
		while (*let != '\0'){
		    printf("%c ",*let);
		    let++;
	    
		}
	    }
	    else{
		printf("\n");
		while (*let != '\0'){
		    printf("%c ",input->word[0]);
		    let++;
		}
		j = input->length;
	    }
	    
	    
	    if (&input == &endnode){
		break;
	    }
	    input = &(input->nextword);
	    
	    
	}
    }
    
}
