#include <cs50.h>
#include <stdio.h>
#include <math.h>

int pick(long number, int start, int length, int mult);
int count(long number);

int main(void)
{
    long number = get_long("Credit Card Number: ");
    int length = count (number);
    if (length == 13 || length == 15 || length == 16)
    {
        //sum of sums
        int sum1 = pick(number, 1, length, 1);
        int sum2 = pick(number, 2, length, 2);
        int total = sum1 + sum2;
        // check last digit
        int end = total % 10;
        //check company
        if (end == 0)
        {
            //check AMEX
            int first2;
            int first;
            //calculate first two digit
            long power2 = pow(10, length - 2);
            long rest2 = (number % power2);
            first2 = (number - rest2)/power2;
            //calculate first digit
            long power = pow(10, length - 1);
            long rest = (number % power);
            first = (number - rest)/power;
            //check company
            //check AMEX
            if ((first2 == 34 || first2 == 37) && length == 15)
            {
                printf("AMEX\n");
            }
            //check VISA
            else if (first == 4 && (length == 13 || length == 16))
            {
                printf("VISA\n");
            }
            //check mastercard
            else if ((first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55) && length == 16)
            {
                printf("MASTERCARD\n");
            }
            //regect if not 3, 4, or 5
            else
            {
            printf("INVALID\n");
            }
        }
        //regect if checksum fails
        else
        {
            printf("INVALID\n");
        }
    }
    //regect if digit count is wrong
    else
    {
        printf("INVALID\n");
    }
}

int pick(long number, int start, int length, int mult)
{
    int sum = 0;
    for (int i = start; i <= length; i += 2)
    {
        //get power of 10
        long mod = pow(10, i);
        //get remainder
        long remainder = number % mod;
        //get previous remainder
        long last = number % (mod/10);
        //get digits
        long result = (remainder - last) / (mod / 10);
        //multiply digits by multiplier
        int product = result * mult;
        //add digits of products
        int digit;
        if (product > 9)
        {
            //add digits of product
            digit = (product % 10) + (((product % 100)-(product % 10))/10);
        }
        else
        {
            //do nothing
            digit = product;
        }
        //sum digits
        sum = sum + digit;
    }
    return sum;
    sum = 0;
}

int count(long number)
{
    int n;
    //until the number is completely gone
    while(number > 0)
    {
        //divide by 10 (remove one digit)
        number = number/10;
        //add 1 to digit count
        n = n + 1;
    }
    return n;
    n = 0;
}