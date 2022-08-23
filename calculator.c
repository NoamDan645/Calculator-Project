#include <string.h> /* strlen */
#include <math.h>   /* pow */
#include <stdlib.h> /* strtod */
#include <assert.h> /* assert */
#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "calculator.h"

/******************* global *********************/

static stack_ty *num_stack = NULL;
static stack_ty *op_stack = NULL;
static int run = 1;

typedef char *(*parse_func_ty)(char *);
typedef double (*exec_func_ty)(double, double);

typedef struct
{
    parse_func_ty parse;
    exec_func_ty exec;
    int precedence;

} char_propeties_ty;

char_propeties_ty funcs_lut[128];


/******************* math function *********************/
static double Plus(double num1, double num2)
{
    return num1 + num2;
}

static double Minus(double num1, double num2)
{
    return num2 - num1;
}

static double Multi(double num1, double num2)
{
    return num1 * num2;
}

static double Division(double num1, double num2)
{
    return num2 / num1;
}

/******************* Execute function *********************/

static char *Execute(char *oper)
{

    while (!StackIsEmpty(op_stack) && funcs_lut[(int)*oper].precedence <= funcs_lut[(int)*(char *)StackPeek(op_stack)].precedence)
    {
        double a = 0.0, b = 0.0;
        a = *(double *)StackPeek(num_stack);
        StackPop(num_stack);
        b = *(double *)StackPeek(num_stack);
        StackPop(num_stack);

        b = funcs_lut[(int)*(char *)StackPeek(op_stack)].exec(a, b);
        StackPush(num_stack, &b);
        StackPop(op_stack);
    }
    StackPush(op_stack, oper);
    return ++oper;
}

char *InsertNum(char *exp)
{
    double digit = strtod(exp, &exp);
    StackPush(num_stack, &digit);
    return exp;
}

char *endExecute(char *exp)
{
    Execute(exp);
    run = 0;
    return exp;
}

char *OpenBracket(char *exp)
{
    StackPush(op_stack, exp);

    return ++exp;
}

char *CloseBarket(char *exp)
{
    while ('(' != *(char *)StackPeek(op_stack))
    {
        double a = 0.0, b = 0.0;
        a = *(double *)StackPeek(num_stack);
        StackPop(num_stack);
        b = *(double *)StackPeek(num_stack);
        StackPop(num_stack);

        b = funcs_lut[(int)*(char *)StackPeek(op_stack)].exec(a, b);
        StackPush(num_stack, &b);
        StackPop(op_stack);
    }
    StackPop(op_stack);
    return ++exp;
}


/******************* init LUT *********************/

void initLut()
{
    size_t index = 0;

    for (index = 0; index < 128; ++index)
    {
        funcs_lut[index].parse = NULL;
        funcs_lut[index].exec = NULL;
        funcs_lut[index].precedence = 0;
    }
    for (index = '0'; index <= '9'; index++)
    {
        funcs_lut[index].parse = InsertNum;
    }

    funcs_lut['+'].parse = Execute;
    funcs_lut['+'].exec = Plus;
    funcs_lut['+'].precedence = 3;

    funcs_lut['-'].parse = Execute;
    funcs_lut['-'].exec = Minus;
    funcs_lut['-'].precedence = 3;

    funcs_lut['*'].parse = Execute;
    funcs_lut['*'].exec = Multi;
    funcs_lut['*'].precedence = 4;

    funcs_lut['/'].parse = Execute;
    funcs_lut['/'].exec = Division;
    funcs_lut['/'].precedence = 4;

    funcs_lut['('].parse = OpenBracket;
    funcs_lut['('].exec = NULL;
    funcs_lut['('].precedence = 1;

    funcs_lut[')'].parse = CloseBarket;
    funcs_lut[')'].exec = NULL;
    funcs_lut[')'].precedence = 2;

    funcs_lut['\0'].parse = endExecute;
}

static char *NextChar(char *str)
{
    assert(str);

    while (isspace(*str) && *str != '\0')
    {
        ++str;
    }

    return str;
}

/************************** Calculator function ***********************************/

double Calculate(const char *expression)
{

    char *next_char = NULL;

    double result = 0;

    initLut();

    num_stack = StackCreate(strlen(expression), sizeof(double));
    op_stack = StackCreate(strlen(expression), sizeof(char));

    next_char = NextChar((char *)expression);

    while (run)
    {
        next_char = funcs_lut[(int)*next_char].parse(next_char);
        next_char = NextChar(next_char);
    }

    result = *(double *)StackPeek(num_stack);

    return result;
}
