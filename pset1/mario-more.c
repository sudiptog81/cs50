/**
 * PSet 2b - Mario - More Comfortable
 * Written by Sudipto Ghosh for CS50
 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initializing an integer variable
    int height = 0;
    
    // prompting user for input and storing
    // it in the 'height' variable
    do
        height = get_int("Height: ");
    while (height < 1 || height > 8);
    
    // print the '#' pyramid of some 'height'
    for (int i = 1; i <= height; i++)
    {
        // print the left pyramid
        // print whitespaces
        for (int j = height - 1; j >= i; j--)
            printf(" ");
        // print hashes
        for (int j = 1; j <= i; j++)
            printf("#");
        
        // print two whitespaces
        printf("  ");
        
        // print the right pyramid
        // print hashes
        for (int j = 1; j <= i; j++)
            printf("#");
        
        // end the line after each row
        printf("\n");
    }
    
    return 0;
}
