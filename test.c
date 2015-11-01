#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct wordnode {
    //array of chars to hold the word (we're told max length is 100)
    char word[ 102 ];//for possibility of length 100 word + newline + \0
    
    //pointer to the next word
    struct wordnode *nextword;
    int length;
    int white;
};

void left (struct wordnode *head, struct wordnode *tail, int width ){
    
    //pointers to the current node and last/first words on the current line
    struct wordnode *current = head;
    struct wordnode *end = tail;
    
    int lc = 0;//linecount
    
    while (current != end) {
        while (lc <= width ){
            if (lc == 0) {//first word on a line
                printf("%s", &(current->word[0]));
                lc += current->length;
                current = current->nextword;
            }
            else if (( lc + current->length + 1) <= width ){//if current word can fit on line
                printf(" %s", &(current->word[0]));
                lc += current->length + 1;
                current = current->nextword;
            }
            else{//need to go to newline
                printf("\n%s",&current->word[0]);
                lc = current->length;
                current = current->nextword;
            }
        }
    }
}

//initialize a root node
struct wordnode rootnode;
//pointer to root node
struct wordnode *input = &rootnode;
//pointer to last node
struct wordnode *tail;
    
int currwidth = 0;
int margin = 0;
int compress = 1;
int alignment = 0;
int width = 72;

int main (void){
    int ch;
    char c;
    int i, j, k, l = 0;
    while ((ch = getchar()) != EOF) {
        if ((ch > 32) && (i<100)){//33 is first ascii value of a valid character
            if (input->white) input->white = 0;//resets white flag
            c = ch;
            input->word[i] = c;
            i++;
            //printf("%c",c);
        }
        else if ((ch == 32) && (!input->white)){//32 is ascii space
            input->length = i;
            input->word[i] = '\0';
            i = 0;
            input->nextword = malloc(sizeof(struct wordnode));
            input = input->nextword;
            input->white = 0;
            //printf(" %d ",input->white );
            //printf(" ");
        }
        else if (ch == 10) {//10 is newline
            //printf("white1:%d\n", input->white);
            if (compress){
                if (input->white == 2){//if needs to be scrubbed
                    //printf("compressed\n");
                }
                else if (input->white){//checking to see if previous is paragraph
                    input->word[0] = '\n';
                    input->word[1] = '\0';
                    input->nextword = malloc(sizeof(struct wordnode));
                    input = input->nextword;
                    input->white = 2;
                    //printf("\n");
                }
                else{//if this is the first newline
                    input->length = i;
                    //input->word[i] = '\n';//inserts newline into word
                    //we will probably remove the above when we begin output
                    //it will add newlines in middle of paragraph
                    input->word[i+1] = '\0';
                    
                    //printf("\n");
                    i = 0;
                    input->white = 1;//sets flag to designate that newline is contained in node
                    input->nextword = malloc(sizeof(struct wordnode));
                    input = input->nextword;//create node of newline and endstring
                    input->white = 1;//denotes previous newline
                }
            }
            else if (input->white){//checking to see if previous is paragraph
                input->word[0] = '\n';
                input->word[1] = '\0';
                input->nextword = malloc(sizeof(struct wordnode));
                input = input->nextword;
                input->white = 0;
                //printf("\n");
            }
            else{//if is the first newline
                input->length = i;
                //input->word[i] = '\n';//inserts newline into word
                //we will probably remove the above when we begin output
                //it will add newlines in middle of paragraph
                input->word[i+1] = '\0';
                
                //printf("\n");
                i = 0;
                input->white = 1;//sets flag to designate that newline is contained in node
                input->nextword = malloc(sizeof(struct wordnode));
                input = input->nextword;//create node of newline and endstring
                input->white = 1;//denotes previous newline
            }
            
            
        }
        tail = input;
    }
    left(&rootnode, tail, 72);

    
    
}
