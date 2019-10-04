/**
 * PSet 2.3 - Crack
 * Written by Sudipto Ghosh for CS50
 */

#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

const int ALPHABETS = 52;
const char *ALPHABET = "\0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main(int argc, char **argv)
{
    // check validity of argument
    if (argc != 2 || argv[1] == NULL)
    {
        // print usage information and exit
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // extract salt from hashed password
    char salt[] = {argv[1][0], argv[1][1], '\0'};
    
    // initialize attempt counter
    int attemptCount = 0;
    
    // initialize password with null characters
    char password[6] = {'\0'};
    
    // iterate over all permutations of ALPHABET
    for (int i = 0; i < ALPHABETS; i++)
    {
        for (int j = 0; j < ALPHABETS; j++)        
        {
            for (int k = 0; k < ALPHABETS; k++)
            {
                for (int l = 0; l < ALPHABETS; l++)        
                {
                    for (int m = 1; m < ALPHABETS; m++)        
                    {
                        // construct password for each permutation
                        password[0] = ALPHABET[m]; // first letter
                        password[1] = ALPHABET[l]; // second letter
                        password[2] = ALPHABET[k]; // third letter
                        password[3] = ALPHABET[j]; // fourth letter
                        password[4] = ALPHABET[i]; // fifth letter
                        
                        // increment attempt counter
                        attemptCount++; 
                        
                        // print password if match found and exit
                        if (!strcmp(crypt(password, salt), argv[1]))
                        {
                            printf("Password: %s\n", password);
                            printf("Attempts: %i\n", attemptCount);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
    
    // print error message if password not cracked
    printf("Password could not be cracked\n");
    
    return 2;
}
