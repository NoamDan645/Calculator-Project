#include <stdio.h>
#include "calculator.h"


/************************* #define ***************************/

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n\n", name, actual == expected ? GREEN "Pass" WHITE : RED "Fail" WHITE)


int main(void)
{
    char *expression = NULL;
    char *expression1 =NULL;
    double calculate  =0;
    double result = 0;
     
/*     expression = "4+2*2";
    result= 4+2*2;
    calculate = Calculate(expression);
    
    printf("calculate = %f\n",calculate);
    printf("result = %f\n",result);

    TEST("result", result, calculate); */

    printf("---------------------------------------\n");

    expression1 = "4+2*2";
    result = 4+2*2;
    calculate = Calculate(expression1);

    printf("calculate = %f\n",calculate);
    printf("result = %f\n",result);

    TEST("result", result, calculate);



    return 0;
}