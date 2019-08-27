// Validate credit card numbers
// Cheyanna Graham
// June 1 2019

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>



void get_card_number(void);
void card_type(long card_number);
void validate(long card_number, string type);

int main(void)
{
    get_card_number();
}

// Prompt user for cc number
void get_card_number(void)
{
    card_type(get_long("\nPlease enter a credit card number\n"));
}

// Determine card type or invalid
void card_type(long card_number) 
{
    char cc[17];
    sprintf(cc, "%li", card_number);
    int cc_length = strlen(cc);
    int first_digit = card_number / pow(10, (cc_length - 1));
    int first_two_digits = card_number / pow(10, (cc_length - 2));
    
    // ViSA Validation
    if (first_digit == 4)
    {
        if (cc_length == 13 || cc_length == 16)
        {
            validate(card_number, "VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    // AMERICAN EXPRESS Validation
    else if (first_two_digits == 34 || first_two_digits == 37)
    {
        if (cc_length == 15)
        {
            validate(card_number, "AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }        
    }
    
    //MASTERCARD VAlIDATION
    else if (cc_length == 16)
    {
        if (first_two_digits == 51 ||
            first_two_digits == 52 ||
            first_two_digits == 53 || 
            first_two_digits == 54 ||
            first_two_digits == 55)
        {
            validate(card_number, "MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    else
    {
        printf("INVALID\n");
    }
}


// Card number checksum
void validate(long cc, string type)
{
    bool multiply_by_two = false;
    int total = 0;
    
    while (cc > 0)
    {
        int mod = cc % 10;
        
        if (multiply_by_two) 
        {
            mod *= 2;
        }
        
        // Add Digits together 10 = 1 ! 10
        if (mod > 9)
        {
            while (mod > 0)
            {
                total += mod % 10;
                mod /= 10;
            }
        }
        else
        {
            total += mod;
        }
        
        cc = cc / 10;
        
        // Multiply every other digit by 2
        multiply_by_two = !multiply_by_two;
    }
    bool congruent = total % 10 == 0;
    printf("%s", congruent ? type : "INVALID\n");
    
}

