#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

/*
 * convert bin str to short; return value
 */

unsigned short get_binary_op(char *bin){

    int value = 0;
    int bin_length;
    int p[16] = {32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1};

    //set all values to zero
    for (int i=0;i<20;i++){
        bin[i] = 0;
    }

    //get binary input
    printf("Enter binary value: ");
    scanf("%s", bin);
    printf("%s\n", bin);
    bin_length = strlen(bin);

    //convert
    for (int i=bin_length-1,j=15;i >= 0;i--,j--){
        value += ((int)bin[i]-48) * p[j];
    }

    value = (unsigned short) value;
    return value;
}


/*
 * read in numeric value in mode; return value
 */


short get_operand(char mode){

    int p;
    short operand;
    //char bin_str[20];

    switch (mode) {

        default:
            break;


        case 'B':
            p = get_binary_op(bin_str);
            break;

        case 'H':
            printf("Enter hex value: ");
            scanf("%04hX", &p);
            printf("%hX\n", p);
            break;

        case 'O' :
            printf("Enter octal value: ");
            scanf("%06ho", &p);
            printf("%ho\n",p);
            break;

        case 'D':
            printf("Enter decimal value: ");
            scanf("%hd", &p);
            printf("%hd\n", p);
            break;

    }


    operand = (short)p;

    return operand;
};



/*
 * convert acc to binary str for output
 */


void convert_to_binary(short acc, char *bin){

    int convert_bin = acc;
    int p[16] = {32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1};

    //negative case
    if(convert_bin < 0){
        convert_bin += 65536;
    }

    //convert to binary
    for (int i = 0; i < 16; i++){

        if (convert_bin % p[i] == convert_bin){
            *(bin+i) = '0';
        }else{
            convert_bin = convert_bin % p[i];
            *(bin+i) = '1';
        }
    }

    //add spaces
    for (int i = 18; i >=15; i--){
        bin[i] = bin[i-3];
    }

    for (int i = 13; i >= 10; i--){
        bin[i] = bin[i-2];
    }

    for (int i = 8; i >= 5; i--){
        bin[i] = bin[i-1];
    }

    bin[4] = ' ';
    bin[9] = ' ';
    bin[14] = ' ';
}


/*
 * call get_operand to get val in mode to add to accum; detect pos/neg overflow
 */

void add(short *acc, char mode){

    int int_acc = *acc;
    short add;
    //char bin_str[20];

    switch (mode) {

        default:
            break;

        case 'B':
            printf("Enter binary value: ");
            add = get_binary_op(bin_str);
            break;

        case 'H':
            printf("Enter hex value: ");
            scanf("%hX", &add);
            printf("%hX\n", add);
            break;

        case 'O':
            printf("Enter octal value: ");
            scanf("%ho", &add);
            printf("%ho\n", add);
            break;

        case 'D':
            printf("Enter decimal value: ");
            scanf("%hd", &add);
            printf("%hd\n", add);
            break;


    }

    //add and detect overflow
    *acc = *acc + add;

    if (int_acc < 0 && add < 0 && *acc > 0){
        printf("Negative Overflow\n");

    }else if(int_acc > 0 && add > 0 && *acc < 0){
        printf("Positive Overflow\n");

    }
}

/*
 *similar to add, but subtract
 */

void subtract(short *acc, char mode){

    int int_acc = *acc;
    short subtract;
    //char bin_str[20];

    switch (mode) {

        default:
            break;

        case 'B':
            printf("Enter binary value: ");
            subtract = get_binary_op(bin_str);
            break;

        case 'H':
            printf("Enter hex value: ");
            scanf("%hX", &subtract);
            printf("%hX\n", subtract);
            break;

        case 'O':
            printf("Enter octal value: ");
            scanf("%ho", &subtract);
            printf("%ho\n", subtract);
            break;
        case 'D':
            printf("Enter decimal value: ");
            scanf("%hd", &subtract);
            printf("%hd\n", subtract);
            break;

    }

    //subtrct and detect overflow
    *acc = *acc - subtract;


    if (int_acc > 0 && subtract < 0 && *acc < 0){
        printf("Positive Overflow\n");

    }else if(int_acc < 0 && subtract > 0 && *acc > 0){
        printf("Negative Overflow\n");

    }

}

/*
 * print out accumulator values
 */
void print_acc (short acc, char mode) {

    //char bin_str[20];
    convert_to_binary(acc, bin_str);

    printf("\n****************************************\n");

    switch(mode){
        case 'B':
            printf("* Accumulator:         Input Mode: Bin *\n");
            break;

        case 'O':
            printf("* Accumulator:         Input Mode: Oct *\n");
            break;

        case 'D':
            printf("* Accumulator:         Input Mode: Dec *\n");
            break;

        case 'H':
            printf("* Accumulator:         Input Mode: Hex *\n");
            break;
    }

    printf("*   Binary  :  %s     *\n", bin_str);
    printf("*   Hex     :  %04hX                    *\n", acc);
    printf("*   Octal   :  %06ho                  *\n", acc);
    printf("*   Decimal :  %-10hd              *\n", acc);
    printf("****************************************\n\n");


}


/*
 * print menu; get option until valid; return option
 */

char print_menu() {

    char input[30];
    char input_list[] = {'C', 'S', '&', '|', '^', '~', '<', '>', '+', '-', 'N', 'Q'};
    char mode;
    int stop = 0;

    //use while loop to get a valid input
    while (stop == 0){

        printf("Please select one of the following options: \n\n"
               "B  Binary Mode             &  AND with Accumulator           +  Add to Accumulator\n"
               "O  Octal Mode              |  OR  with Accumulator           -  Subtract from Accumulator\n"
               "H  Hexadecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator\n"
               "D  Decimal Mode            ~  Complement Accumulator\n\n"
               "C  Clear Accumulator       <  Shift Accumulator Left\n"
               "S  Set Accumulator         >  Shift Accumulator Right\n\n");

        printf("Q  Quit \n\n");

        scanf("%s", input);
        printf("Option: ");

        if (strlen(input) > 1){

            printf("%s\n\n", input);
            printf("Invalid option: %s\n\n", input);

        }else{

            mode = input[0];

            if ((mode >= 97) && (mode <= 122)) {
                mode = toupper(input[0]);
            }

            if (mode == 'O'){
                stop++;
                printf("%c\n", input[0]);
                printf("Mode is Octal\n");
                break;

            }else if (mode == 'H'){
                stop++;
                printf("%c\n", input[0]);
                printf("Mode is Hexadecimal\n");
                break;

            }else if (mode == 'D'){
                stop++;
                printf("%c\n", input[0]);
                printf("Mode is Decimal\n");
                break;

            }else if (mode == 'B'){
                stop++;
                printf("%c\n", input[0]);
                printf("Mode is Binary\n");
                break;

            }else{

                int temp = 0;
                for(int i = 0; i < 12; i++){
                    if (input_list[i] == mode){
                        temp++;
                    }
                }

                if (temp == 1){
                    stop++;
                    printf("%c\n", input[0]);
                    break;

                }else{
                    printf("%c\n", input[0]);
                    printf("\n");
                    printf("Invalid option: %c\n", input[0]);
                    printf("\n");

                }
            }
        }
    }

    return mode;
}


/*
 * main menu loop; execute option or call appropriate function
 */


int main() {

    //initializtion
    char mode = 'D';
    char input;
    short acc = 0;
    int quit = 0;
    short operand;
    short *value = &acc;
    //char bin_str[20];


    while (quit == 0){

        print_acc(acc,mode);
        input = print_menu();

        switch (input) {

            default:
                break;

            case 'D':
                mode = 'D';
                break;

            case 'B':
                mode = 'B';
                break;

            case 'H':
                mode = 'H';
                break;

            case 'O':
                mode = 'O';
                break;

            case 'S':
                if (mode == 'B'){
                    acc = get_binary_op(bin_str);
                    break;
                }else{
                    acc = get_operand(mode);
                    break;
                }

            case 'C':
                acc = 0;
                break;

            case 'Q':
                quit = 1;
                break;

            case '&':

                switch (mode){

                    case 'B':
                        printf("Enter binary value: ");
                        operand = get_binary_op(bin_str);
                        break;

                    case 'H':
                        printf("Enter hex value: ");
                        scanf("%hX", &operand);
                        printf("%04hX\n", operand);
                        break;

                    case 'O':
                        printf("Enter octal value: ");
                        scanf("%ho", &operand);
                        printf("%ho\n", operand);
                        break;

                    case 'D':
                        printf("Enter decimal value: ");
                        scanf("%hd", &operand);
                        printf("%hd\n", operand);
                        break;



                }

                acc = acc & operand;
                break;

            case '|':

                switch (mode){

                    case 'B':
                        printf("Enter binary value: ");
                        operand = get_binary_op(bin_str);
                        break;

                    case 'H':
                        printf("Enter hex value: ");
                        scanf("%hX", &operand);
                        printf("%04hX\n", operand);
                        break;

                    case 'O':
                        printf("Enter octal value: ");
                        scanf("%ho", &operand);
                        printf("%ho\n", operand);
                        break;

                    case 'D':
                        printf("Enter decimal value: ");
                        scanf("%hd", &operand);
                        printf("%hd\n", operand);
                        break;

                }

                acc = acc | operand;
                break;

            case '^':

                switch (mode){

                    case 'B':
                        printf("Enter binary value: ");
                        operand = get_binary_op(bin_str);
                        break;

                    case 'H':
                        printf("Enter hex value: ");
                        scanf("%hX", &operand);
                        printf("%04hX\n", operand);
                        break;

                    case 'O':
                        printf("Enter octal value: ");
                        scanf("%ho", &operand);
                        printf("%ho\n", operand);
                        break;

                    case 'D':
                        printf("Enter decimal value: ");
                        scanf("%hd", &operand);
                        printf("%hd\n", operand);
                        break;
                }

                acc = acc ^ operand;
                break;

            case '<':
                printf("Enter number of positions to left shift accumulator: ");
                scanf("%hd", &operand);
                printf("%hd\n", operand);
                operand = (int)operand;
                acc = acc << operand;
                break;

            case '>':
                printf("Enter number of positions to right shift accumulator: ");
                scanf("%hd", &operand);
                printf("%hd\n", operand);
                operand = (int)operand;
                acc = acc >> operand;
                break;

            case '~':
                acc = ~acc;
                break;

            case 'N':
                acc = -acc;
                break;

            case '+':
                add(value, mode);
                break;

            case '-':
                subtract(value, mode);
                break;

        }



    }

    return 0;
}


