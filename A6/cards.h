//
// Created by Xianglu Peng on 11/2/20.
//

#ifndef A6_CARDS_H
#define A6_CARDS_H

#include "callouts.h"

typedef struct CARD{

    int player;
    int grid[5][5];
    char called[5];
    struct CARD *next;

}CARD_T;

void init_cards (int num_players, CARD_T **list, char *fns []);
void update_grid (CARD_T *pcard, CALLOUT_T callout);
int check_grid (CARD_T *pcard);
int update_cards (CALLOUT_T call_num, CARD_T *list);
void print_cards (CARD_T *list);
void free_cards (CARD_T **list);

#endif //A6_CARDS_H
