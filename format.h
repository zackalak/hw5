void left ( struct wordnode *head, struct wordnode *tail, int width ) {

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
