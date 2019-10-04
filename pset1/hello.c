/**
 * PSet 1 - Hello
 * Written by Sudipto Ghosh for CS50
 */

#include <stdio.h>

int main(void)
{
    char answer[255];
    printf("What\'s your name?\n");
    scanf("%s", answer);
    printf("hello, %s\n", answer);
    return 0;
}
