#include <stdio.h>

int const devider = 2;
int num;
void decimalToReversedBinary();

int main() {

    do{

        printf("\nGive a positive integer number or 0 to exit \n");
        scanf("%d", &num);
        (num < 0? main() : decimalToReversedBinary(num));

    }while(num!=0);


    return 0;
}

void decimalToReversedBinary(int number){

    int remainder;
    char remainderChar;

    while(number >= 1){

        remainder = number%2;
        number = number/2;
        remainderChar = remainder + '0';
        putchar(remainderChar);
    }
}
