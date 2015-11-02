#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct wordnode {
    //array of chars to hold the word (we're told max length is 100)
    char word[ 101 ]; //for possibility of length 100 word + \0
    //pointer to the next word
    struct wordnode *nextword;
    int length;
};

void left (struct wordnode *head, struct wordnode *tail, int width ){

    //pointer to the current node
    struct wordnode *current = head;
    int lc = 0; //linecount
    
    while ( lc <= width ){
        if ( lc == 0 ) { //first word on a line
            printf("%s", &( current->word[0] ) );
            lc += current->length;
        }
        else if (( lc + current->length + 1) <= width ) { //if current word can fit on line
            printf( " %s", & (current->word[0] ) );
            lc += current->length + 1;
        }
        else { //need to go to newline
            printf( "\n%s", &( current->word[0] ) );
            lc = current->length;
        }
	if ( current->nextword != tail ) current = current->nextword;
	else break;
    }
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
	    if ( current->nextword != tail && currwidth + 1 + (*(*current).nextword).length <= width ) {
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

//initialize a root node
struct wordnode rootnode;
//pointer to root node
struct wordnode *input = &rootnode;
//pointer to last node
struct wordnode *tail;
    
int compress = 1;
int alignment = 0; //0=left, 1=right, 2=full
int width = 72;

int main ( int argc, char *argv[] ) {
    int ch;
    char c;
    int i = 0; 
    int j = 0;
    int nonempty =  0;
    int para = 0; //are we still between paragraphs
    
    printf ( "%s %d", "number of args is:", argc );
    while (j < argc) {
	//printf("argument is: %s\ni=%d", argv[i],i);
	if (!strcmp(argv[j] , "-w")){
	    //width flag
	    j++;
	    //printf("width start\n");
	    width = atoi(argv[i]);
	    j++;
	    //printf("width end - %d", width);
	    }
	
	else if (!strcmp(argv[i] , "-r")){
	    //right alignment
	    alignment = 1;
	    j++;
	    //printf("right\nalignment=%d", alignment);
	}
	else if (!strcmp(argv[i] , "-j")){
	    //justified
	    alignment = 2;
	    j++;
	    //printf("justified\nalignment=%d", alignment);
	}
	else if (!strcmp(argv[i] , "-s")){
	    //compress spaces
	    compress = 1;
	    j++;
	    //printf("compress");
	}
	else if ((!strcmp(argv[i] , "-h")) || (!strcmp(argv[i] , "-?"))){
	    printf("Usage message**");
	    return 0;
	    //print usage message and exit program
	}
    }

    while ((ch = getchar()) != EOF) {
        if ( ch != ' ' && ch != '\n' ) { 
	    nonempty = 1;
	    
	    if ( para > 0 ) { //we've read in a full paragraph of input plus separating lines
		switch ( alignment ) {
		    case 0 :
			left ( head, tail, width );
		    case 1 :
			right ( head, tail, width );
		    case 2 :
			right ( head, tail, width );
		}
		if ( compress ) { //only one newline
		    printf ( "\n" );
		}
		else { //print out all the blank lines we've seen
		    for ( ; para > 0; para-- ) {
			printf ( "\n" );
		    }
		}
		para = 0;
		//free memory and reassign root here
	    }

	    while ( ch != ' ' && ch != '\n' ) {
		c = ch;
		input->word[i] = c;
		i++;
		ch = getchar();
	    }

	    ungetc ( ch, stdin );
	    input->length = i;
            input->word[i] = '\0';
            i = 0;
            input->nextword = malloc( sizeof ( struct wordnode ) );
            input = input->nextword;
	}

	//if ch is whitespace
	else {    
	    //consume chars until we get something we want
	    while ( ch != EOF ) {
		//ch is a newline
		if ( ch == '\n' ){
		    //if the line has a word
		    if ( nonempty ) {
			nonempty = 0;
			break;
		    }
		    else { //empty line
			printf ( "empty line\n" );
			para++;
		    }
		}
		//ch is a space 
		else if ( ch == ' ' ) {
		    ch = getchar();
		    continue;
		}
		//ch is something we want
		else {
		    //put it back so the word loop can get it
		    ungetc( ch, stdin );
		    break;
		}
	    }
        }

    }
    tail = input;
    left(&rootnode, tail, 20);    
}
