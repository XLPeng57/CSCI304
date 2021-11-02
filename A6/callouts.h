//
// Created by Xianglu Peng on 11/2/20.
//

#ifndef A6_CALLOUTS_H
#define A6_CALLOUTS_H

#include "bingo.h"

typedef struct CALLOUT{
    int number;
    enum BINGO_T letter;
}CALLOUT_T;

void init_callouts (char *fn);
char *get_callout_str (CALLOUT_T callout);
CALLOUT_T get_callout (void);
void free_callouts (void);

#endif //A6_CALLOUTS_H
