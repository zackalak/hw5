//For right alignment and fullly justified formatting we need to know the maximum number of words
//that can fit on a given line **before** we do any formatting.
//Thus, we have to read the words and compute that value before we can print anything.
//
//We're told that there's no max line length for input,
//so we can't make a pointer to the whole line--we don't know if it will be big enough.
//The only max value we're given is for words, which we're told is 100 chars.
//
//I thought that the easiest way to satisfy all the above would be:
//create a linked list of strings representing all of our input, and then traverse it while doing the formatting line-by-line.
//
//The code below does this but doesn't apply any formatting.
//Right now it's also missing spaces because the call to scanf() consumes them.
//Also, it would probably be better to for the scanf() call to read in chars until whitespace for each word and increment the length member
//each time.
//Right now, with %s as the format, it automatically does this, but we can't get a length value: it only returns the number of matches
//per call, which will always be 1 (ie, one whitespace-separated word was found).
//
//The only trouble I could see with this approach is conversion formatting if there are numbers in the input.
//Maybe we could add a flag in the struct for conversion when it's time to print?
//
//----------------------------------------------------------------------------------------------------
//I compiled with:
//  gccx -o inputtest inputtest.c
//
//I tested with:
//  echo "the big red dog" | ./inputtest
//which gives as ouput:
//  thebigreddog

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//basic node struct in a linked list of words
struct wordnode {
    //array of chars to hold the word (we're told max length is 100)
    char word[ 100 ];
    
    //pointer to the next word
    struct wordnode *nextword;
    int length;
};
void justified ( struct wordnode *head, struct wordnode *tail, int width ) {
}
void right ( struct wordnode *head, struct wordnode *tail, int width ) {

    //pointers to the current node and last/first words on the current line
    struct wordnode *current = head;
    struct wordnode *lastonline;
    struct wordnode *firstonline = head;
    
    int currwidth = 0;
    int margin = 0;
    
    while ( current != tail ) {
	while ( currwidth <= width ) {
	    currwidth += current->length;
	    
	    //next word can fit on the line
	    if ( currwidth + 1 + (*(*current).nextword).length <= width ) {
		//traverse the list
		currwidth++;
		current = current->nextword;
	    }

	    //next word doesn't fit on the line
	    else {
		lastonline = current;
		break;
	    }
	}

    //print out the line
	margin = width - currwidth;
	//print [margin] spaces
	for ( int i = 0; i < margin; i++ ) printf ( " " );
	
	current = firstonline;
	while ( current != lastonline ) {
	    fputs( current->word, stdout );
	    printf( " " );
	    current = current->nextword;
	}

	printf( "%s\n", lastonline->word );
	current = lastonline->nextword;
	firstonline = current;
	currwidth = 0;
    }
}

int alignment = 0;
int compress = 0;
int width = 72;

int main (int argc, char *argv[]) {
    
    //initialize a root node
    struct wordnode rootnode;
    //pointer to root node
    struct wordnode *input = &rootnode;
    //pointer to last node
    struct wordnode *tail;
    
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
	    printf("Format is a simple program that takes in text and outputs it in neatened paragraphs\n");
	    printf("for more information please see the manpage for format.");
	    return 0;
	    //print usage message and exit program
	}
	
    }


    //char blanks[ 100 ] = "";

    //TODO: handle args

    //infinite while, broken when we get EOF
    while (1) {
	//test for empty lines

	if (( scanf ( "%[^\x20-\x7F]", &(input->word[0]) ) != EOF )) {
	    input->length = 1;//strlen( input->word );
	    
	    //no EOF: there are more words, so we add on to the end of the list
	    input->nextword = malloc( sizeof( struct wordnode ) );
	    //point input to it for the next iteration of the loop
	    input = input->nextword;
	    
	    //printf ( "got a newline\n" );
	    //printf ( "%d", strlen ( blanks ) );

	}
	
	else if ( scanf( "%s", &( input->word[ 0 ] ) ) != EOF ) { 
	    input->length = strlen( input->word );
	    
	    //no EOF: there are more words, so we add on to the end of the list
	    input->nextword = malloc( sizeof( struct wordnode ) );
	    //point input to it for the next iteration of the loop
	    input = input->nextword;
	    
	}
	else {	
	    tail = input;
	    break;
	}
    }

    if (alignment == 1){
	right ( &rootnode, tail, width );
    }
    else if (alignment == 0){
	left (&rootnode, tail, width);
    }
    else if (alignment == 2){
	justified (&rootnode, tail, width);
    }
}


