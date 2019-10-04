
/**
 * PSet 2.1 - Caesar
 * Written by Sudipto Ghosh for CS50
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // check validity of command-line argument
    bool isValid = true;
    // there should be only 2 arguments
    if (argc != 2)
    {
        isValid = false;
    }
    else if (argv[1] == NULL)
    {
        isValid = false;
    }
    else
    {
        // iterate over each element of the argument
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')
            {
                isValid = true;
            }
            else
            {
                isValid = false;
            }
        }
    }
      
    // check if 'isValid' flag is false
    if (!isValid)
    {
        // print usage information and exit
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // convert argument to integer
    int k = atoi(argv[1]);
    
    // prompt user for plain-text input
    char *text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    // iterate over each character of the input
    for (int i = 0; i < strlen(text); i++)
    {
        // rotation for uppercase letters
        if (isupper(text[i]))
        {
            // print rotated letter
            printf("%c", 65 + ((text[i] + k) - 65) % 26);
        }
        // rotation for lowercase letters
        else if (islower(text[i]))
        {
            // print rotated letter
            printf("%c", 97 + ((text[i] + k) - 97) % 26);
        }
        // no rotation for elements not in [Aa-Zz]
        else
        {
            // print letter as-it-is
            printf("%c", text[i]);
        }
    }
    
    // print a new line
    printf("\n");
    
    return 0;
}
