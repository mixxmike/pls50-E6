#include <stdio.h>

double firstNum, secondNum;
char operand;

void operation(double num1, double num2, char operand);

int main() {

    printf("Give number operation number \n");
    scanf("%lf %c %lf", &firstNum, &operand, &secondNum);
    operation(firstNum, secondNum, operand);

    return 0;
}

void operation(double num1, double num2, char operand){

    double result;

    switch(operand) {
      case '+' :
         result = num1 + num2;
         printf("The result is: %.2lf\n", result);
         break;
      case '-' :
         result = num1 - num2;
         printf("The result is: %.2lf\n", result);
         break;
      case '*' :
         result = num1 * num2;
         printf("The result is: %.2lf\n", result);
         break;
      case '/' :
          if(num2 == 0){

            printf("Division by zero not allowed");
            break;
          }

         result = num1 / num2;
         printf("The result is: %.2lf\n", result);
         break;
      default :
         printf("Invalid input\n" );
   }
}
