#include <stdio.h>

/*computes the summation of 𝒊𝟐 using repeated adds*/

int sumsq(int n){

    int num;
    int sum=0;
    for (int j=1;j<n+1;j++){
        num=0;
        for (int i=0;i<j;i++){
            num += j;
        }
        sum += num;
    }

    return sum;
}


/*loop through n from 1 to 10 call sumsq with n
 * and save its return value print n in decimal;
 * print sumsq return value on n in decimal and hex*/

int main() {

    int sum;

    for (int i=1;i<11;i++){
        printf("%2d:  ",i);
        sum = sumsq(i);
        printf("%3d  ", sum);
        printf("%3x\n",sum);
    }




    return 0;
}
