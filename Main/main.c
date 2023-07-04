#include <stdio.h>

int main(void)
{

    FILE *fp; // file pointers
    fp = fopen("database/test.txt", "w");
    fprintf(fp, "Hello, World!");

    fclose(fp);
    return 0;
}