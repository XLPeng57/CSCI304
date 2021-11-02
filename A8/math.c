#include <stdio.h>


//returns the absolute value of n
int abs(int n){

    if (n > 0){
        return n;
    }else{
        return 0 - n;
    }
}

//computes and returns the product of x and y
//by repeatedly adding y to itself x times
//(this function should be called with x < y, when possible)

int mult(int x, int y){

    int sum = 0;
    if (x > y){
        int tmp = x;
        for(int i=0;i<y;i++){
            sum = sum + tmp;
        }
    }else{
        int tmp = y;
        for(int i=0;i<x;i++){
            sum = sum + tmp;
        }
    }


    return sum;
}

//computes and returns the factorial value of
//n through recursion (see IA32 rfact in slides)

int rfact(int n){

    int result;
    if ( n <= 1)
        result = 1;
    else
        result = mult(n, rfact(n-1));
    return result;

}


int main(){

    // initialize array
    int array[4] = {1,-1,12,0};

    int i = 0;
    while (array[i] != 0){

        int input = array[i];
        printf("%d \n",input);
        printf("%#010x \n", input);

        // call abs to get absolute value of num and print in hex
        int abs_value = abs(input);
        printf("%#010x \n", abs_value);

        // call mult with appropriate arguments to get square of num and print in hex
        int square = mult(abs_value,abs_value);
        printf("%#010x \n", square);


        // call mult to get cube of abs (num) (you may use previous results)
        // and print in hex
        int cube = mult(abs_value,square);
        printf("%#010x \n", cube);

        // call rfact to get factorial of abs(num) and print in hex
        int factorial = rfact(abs_value);
        printf("%#010x \n", rfact(abs_value));


        int lsb = 15 ;
        // if num is odd set lsb of status byte to 1
        if (abs_value % 2 == 0){
            lsb = lsb & 14;
        }


        // if num is negative, set next lsb of status byte to 1
        if (input > 0){
            lsb = lsb & 13;
        }


        // if factorial of num > square of num, set next lsb of status byte to 1
        if(factorial<square){
            lsb = lsb & 11;
        }


        // if factorial of num > cube of num, set next lsb of status byte to 1
        if(factorial<cube){
            lsb = lsb & 7;
        }


        // print status byte in hex
        printf("%#010x \n", lsb);
        i++;
    }


}
