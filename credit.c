// Program to get a credit card number from user, check if the number is valid, and return the credit card type for valid credit card numbers

#include <stdio.h>
#include <cs50.h>

long get_credit_card_number();
int get_number_size(long n);
int sum_digits(long n);
bool validate_checksum(long n);
string check_cc_type(long n);

int main(void)
{
    long cc_number = 0;
    bool isvalid = false;
    string type = "";
   
    // Get user input
    cc_number = get_credit_card_number();
    
    // Check if user entered number is in a reasonable credit card length range
    if (get_number_size(cc_number) < 12) 
    {
        printf("INVALID\n");
        return 0;
    }
    
    // Validate if entered cc number has valid checksum
    isvalid = validate_checksum(cc_number);
    
    // If checksum is valid, then check it's cc type
    if (isvalid == true)
    {
        printf("%s\n", check_cc_type(cc_number));
    }
    else
    {
        printf("%s\n", "INVALID");
    }
    
}

// Returns credit card number from user
long get_credit_card_number()
{
    
    long number = get_long("Number:  ");
    return number;
}

// Returns the length of a number
int get_number_size(long n)
{
    int length = 0;
    long remainder = 0;
    int first_sum = 0;
    
    // Get the remainder dividing the number by 10. The remainder is digit in the 1th position
    // Continue to divide the number by 10 until the remainder is equals 0
    while (n != 0)
    {
        remainder = n % 10;
        n = n / 10;
        length ++;
    }
    return length;
}

// Returns the sum of digit(s) in a number
int sum_digits(long n)
{
    long remainder = 0;
    long sum = 0;
     
    while (n != 0)
    {
        remainder = n % 10;   
        n = n / 10;
        sum = sum + remainder;
    }
    return sum;
}

// Returns true if checksum is valid using Luhn's Algorithm and returns false otherwise
bool validate_checksum(long n)
{
    long remainder = 0;
    int first_sum = 0;
    int size = 0;
    int second_sum = 0;
    int total_sum = 0;
    bool isvalid = false;
    
    // Iterate until the remainder is 0
    while (n != 0)
    {
        size ++;
        int t = 0;
        remainder = n % 10;
        n = n / 10;
       
        // Add sum beginning from second-to-last digit
        if (size % 2 == 0)
        {
            first_sum = first_sum + sum_digits(remainder * 2);
        }
        // Add sum for digit's that weren't multiplied by 2
        else 
        {
            second_sum = second_sum + remainder;     
        }
        
    }
    
    // Add the two sums from the calculation in the while loop above
    total_sum = first_sum + second_sum;
    
    // get the last digit in the total sum
    int last_digit = total_sum % 10;
    
    if (last_digit == 0)
    {
        isvalid = true;
    }
    else 
    {
        isvalid = false;
    }
    
    return isvalid;
}

// Returns credit card type using the following rule. All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55; and all Visa numbers start with 4. 
string check_cc_type(long n)
{
    long remainder = 0;
    int position = 0;
    int first_digit = 0;
    int second_digit = 0;
    string type = "";
    
    int length = get_number_size(n);
    
    while (n != 0) 
    {
        position ++;
        remainder = n % 10;
        // If digit is the second digit in the number then save that digit in a variable
        if (position == length - 1)
        {
            second_digit = remainder;
        }
        // If digit is the first digit in the number then save that digit in a variable
        if (position == length)
        {
            first_digit = remainder;
        }
        
        n = n / 10;    
    }
    
    if (first_digit == 4)
    {
        type = "VISA";
    }
    else if (first_digit == 3 && (second_digit == 4 || second_digit == 7))
    {
        type = "American Express";
    }
    else if (first_digit == 5 && (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4 
                                  || second_digit == 5))
    {
        type = "MasterCard";
    }
    else 
    {
        type = "INVALID";
    }
    return type;
}
