#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int i;

    for ( i = 3; i > 0; i--)
    {
        printf("%d...\n", i);
        sleep(1); // Delay for 1 second 
    }
    system("cls");
    printf("Login Successfully\n");

    // Rest of the program Logic. 
    return 0;
}