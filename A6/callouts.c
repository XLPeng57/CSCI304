//
// Created by Xianglu Peng on 11/2/20.
//
#include <stdio.h>
#include <stdlib.h>
#include "callouts.h"


static CALLOUT_T *array;

/**
 * Run through the file to find how many callouts
 * Allocate space for the dynamic array
 * @param fn
 */
void init_callouts (char *fn){

    FILE *fd;
    char *str;
    int num_of_line = 0;
    fd = fopen(fn,"r");
    while(fscanf(fd, "%s", str)==1){
        num_of_line ++;
    }

    array = malloc(sizeof(CALLOUT_T)*num_of_line);
    rewind(fd);

    enum BINGO_T letter;
    char letter_temp;
    int num;

    for(int i=0; i<num_of_line;i++){
        fscanf(fd, "%c%2d\n", &letter_temp, &num);
        CALLOUT_T call;
        call.number = num;
        switch (letter_temp)
        {
            case 'B':
                letter = B;
                call.letter = letter;
                array[i] = call;
                break;

            case 'I':
                letter = I;
                call.letter = letter;
                array[i] = call;
                break;

            case 'N':
                letter = N;
                call.letter = letter;
                array[i] = call;
                break;

            case 'G':
                letter = G;
                call.letter = letter;
                array[i] = call;
                break;

            case 'O':
                letter = O;
                call.letter = letter;
                array[i] = call;
                break;

            default:
                break;
        }
    }

}
/**
 * converts callout to printable string
 * @param callout
 * @return str
 */

char *get_callout_str (CALLOUT_T callout){
    static char str[5];
    sprintf(str,"%c%d", "BINGO"[callout.letter], callout.number);
    return str;

}

/**
 * returns next callout from array (use static variable to hold current index)
 * @return CALLOUT_T
 */
CALLOUT_T get_callout (void){
    static int count = -1;
    count++;
    return array[count];

}


void free_callouts (void){
    free(array);
}