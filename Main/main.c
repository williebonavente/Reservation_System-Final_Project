#include <stdio.h>
#include "../libs/hello.h"
#include "../libs/input.h"

int main(void)
{
    int input = getInput();
    helloWorld();

    printf("%i ", input);

    return 0;
}
