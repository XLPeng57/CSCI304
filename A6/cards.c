//
// Created by Xianglu Peng on 11/2/20.
//

#include "cards.h"
#include <stdio.h>
#include <stdlib.h>


static void init_card (int grid [][5], char *fn){

    FILE *fd;
    int temp;
    fd = fopen(fn,"r");

    for (int i=0; i<5; i++){
        for(int j=0; j<5;j++){
            fscanf(fd,"%d",&temp);
            grid[i][j] = temp;
        }
    }

}



void init_cards (int num_players, CARD_T **list, char *fns []){


    CARD_T *node, *prev, *head;
    head = NULL;

    for (int i=0; i<num_players; i++){

        node = malloc(sizeof(struct CARD));
        node -> player = i+1;
        init_card(node->grid, fns[i+1]);

        char a = 0; //00000001
        char b = 4; //00000100
        node -> called[0] = a;
        node -> called[1] = a;
        node -> called[2] = b;
        node -> called[3] = a;
        node -> called[4] = a;

        node -> next = NULL;

        if (head == NULL){
            head = node;
        }else{
            prev -> next = node;
        }
        prev = node;
        *list = head;

    }

}

/**
 * Go through each row to see if the number matches
 * if matches, set the bit associate to that location to 1
 * @param pcard
 * @param callout
 */
void update_grid (CARD_T *pcard, CALLOUT_T callout){
    int value = callout.number;
    int col = callout.letter;


    for (int i=0;i<5;i++){
        if (pcard -> grid [i][col] == value){
            char check = 1;
            pcard -> called[i] = (pcard -> called[i] | (check << (4-col)));
        }

    }



}

/**
 * check horizontally/vertically/diagonally if all 1
 * @param pcard
 * @return
 */
int check_grid (CARD_T *pcard){

    int test;

    //check horizontally
    for (int i=0;i<5;i++){
        if (pcard -> called[i] == 31){ //31 = 00011111
            return 1;
        }
    }

    //check vertically
    for (int i=0;i<5;i++){
        test = 0;
        for(int j=0; j<5; j++){
            char check = 1; // 00000001

            if ((check << (4-i) & pcard ->called[j]) != 0){
                test++;

            }
        }
        if (test == 5){
            return 1;
        }
    }

    //check diagonally
    test = 0;
    for (int i=0;i<5;i++){
        char check = 1;

        if (( check << (4-i) & pcard ->called[i]) != 0){
            test++;
        }
    }
    if (test == 5){
        return 1;
    }

    test = 0;
    for (int i=0;i<5;i++){
        char check = 1;

        if (( check << i & pcard ->called[i]) != 0){
            test++;
        }
    }
    if (test == 5){
        return 1;
    }

    return 0;

}


/**
 * Loop through each node in the list
 * call update_grid
 * call check_grid
 * @param call_num
 * @param list
 * @return
 */
int update_cards (CALLOUT_T call_num, CARD_T *list){
    CARD_T *current = list;

    int check_winner;
    int temp = 1;

    printf("callout: %s\n\n", get_callout_str(call_num));
    while (current != NULL){
        update_grid(current,call_num);
        check_winner = check_grid (current);

        if (check_winner == 1){
            printf("\nPlayer %d: BINGO!\n\n", temp);
            return 1;
        }
        temp++;
        current = current -> next;



    }
    return 0;

}

void print_cards (CARD_T *list){

    CARD_T *current = list;

    int tmp = 1;
    while (current != NULL){
        printf("Player %d                               Callouts Marked\n", tmp);
        printf(" -----------------------------         -----------------------------\n"
               "|  B  |  I  |  N  |  G  |  O  |       |  B  |  I  |  N  |  G  |  O  |\n");

        for (int i=0;i<5;i++){
            printf("|-----+-----+-----+-----+-----|       |-----+-----+-----+-----+-----|\n");
            for(int j=0; j<5;j++){

                int temp = current -> grid[i][j];
                if (i==2 && j==2){
                    printf("|  *  ");
                }else{
                    printf("|%4d ", temp);
                }


            }
            printf("|       ");

            for(int j=0; j<5;j++){

                int temp = current -> grid[i][j];
                char check = 1; // 00000001
                if (( check << (4-j) & current ->called[i]) != 0){
                    printf("|  *  ");
                }else{
                    printf("|%4d ", temp);
                }


            }
            printf("|\n");
        }
        printf(" -----------------------------         ----------------------------- \n\n");
        tmp++;
        current = current -> next;


    }



}

void free_cards (CARD_T **list){

    //loop
    CARD_T *current = *list;

    while (current != NULL){

        free(current);
        current = current -> next;


    }

}