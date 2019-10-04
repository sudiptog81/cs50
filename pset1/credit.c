/**
 * PSet 1.3b - Credit
 * Written by Sudipto Ghosh for CS50
 */

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // declare essential variables
    int cardType = 0;
    long cardNumber = 0l;
    
    // prompt user for card number
    // and assign it to 'cardNumber'
    do
    {
        cardNumber = get_long("Number: ");
    }
    while (cardNumber <= 0);  
    
    // calculate number of digits
    int digits = 0;
    long validation = cardNumber;
    while (validation > 0)
    {
        validation /= 10;
        digits++;
    }
    
    // find out checksum digits * 2
    int checksumDigits[8] = {0};
    for (int i = 0, j = 1; i < 8; i++, j += 2)
    {
        checksumDigits[i] = (int)(cardNumber / (long)(pow(10, j)) % 10 * 2);        
    }
    
    // calculate sum of digits of the products
    int sum = 0;
    for (int i = 0;  i < 8; i++)
    {
        for (int j = 0; j < 2; j++, checksumDigits[i] /= 10)
        {
            sum += checksumDigits[i] % 10;
        }
    }
    
    // add remaining digits of card number to sum
    for (int i = 0, j = 0; i < 8; i++, j += 2)
    {
        sum += (int)(cardNumber / (long)(pow(10, j)) % 10);        
    }
    
    // check one's digit of the total
    if (sum % 10 != 0)
    {
        cardType = -1;
    }
    else
    {
        // check starting digits of credit cards
        switch (digits)
        {
            case 13:
                if (cardNumber / (long)(pow(10, 12)) == 4)
                {
                    cardType = 1;
                }
                else
                {
                    cardType = -1;
                }
                break;
            case 15:
                if (cardNumber / (long)(pow(10, 13)) == 34 ||
                    cardNumber / (long)(pow(10, 13)) == 37)
                {
                    cardType = 3;
                }
                else
                {
                    cardType = -1;
                }
                break;
            case 16:
                if (cardNumber / (long)(pow(10, 15)) == 4)
                {
                    cardType = 1;
                }
                else if (cardNumber / (long)(pow(10, 14)) == 51 ||
                         cardNumber / (long)(pow(10, 14)) == 52 ||
                         cardNumber / (long)(pow(10, 14)) == 53 ||
                         cardNumber / (long)(pow(10, 14)) == 54 ||
                         cardNumber / (long)(pow(10, 14)) == 55)
                {
                    cardType = 2;
                }
                else
                {
                    cardType = -1;
                }
                break;
            default:
                cardType = -1;
                break;
        }
    }
    
    // print card type
    switch (cardType)
    {
        case 1:
            printf("VISA\n");
            break; 
        case 2:
            printf("MASTERCARD\n");
            break;
        case 3:
            printf("AMEX\n");
            break;
        case -1:
            printf("INVALID\n");
            break;
    }
    
    return 0;
}
