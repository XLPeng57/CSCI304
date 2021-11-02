//
// Created by Xianglu Peng on 11/2/20.
//

#include "bingo.h"
#include "cards.h"
#include "callouts.h"
#include <stdio.h>


int main(int argc, char *argv[]){


    struct CARD *list = NULL;


    int num_player;
    num_player = argc-2;


        init_cards(num_player, &list, argv);
        init_callouts(argv[argc-1]);

        print_cards(list);
        printf("\n");
        int check;
        int five = 0;
        do{
            CALLOUT_T call = get_callout();
            check = update_cards(call,list);
//            printf("callout: %s\n\n", get_callout_str(call));
            five++;

            if (five % 5 == 0){
                printf("\n");
                print_cards(list);
            }


        }while(check == 0);

        print_cards(list);

    free_cards(&list);
    free_callouts();
    return 0;
}
