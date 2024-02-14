#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int scan(string passage, int target);

int main(void)
{
    //get the passage
    string passage = get_string("Enter Passage: ");
    //get letter count
    float letters = scan(passage, 0);
    //get word count (# of spaces + 1)
    float words = scan(passage, 1) + 1;
    //get sentence count (# of .s)
    float sentences = scan(passage, 2);
    //calculate letters per 100 words
    float l = letters / words * 100;
    //calculate sentences per 100 words
    float s = sentences / words * 100;
    //calculate index
    int index = round(0.0588 * l - 0.296 * s - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

//scanner
int scan(string passage, int target)
{
    //scan through until POI found
    int i = 0;
    int count = 0;
    while (passage[i] > 0)
    {
        char character = passage[i];
        //for 0 (characters)
        if (target == 0)
        {
            if (isalpha(character))
            {
                count = count + 1;
            }
        }
        //convert 1 (words) to accepted ASCII values
        else if (target == 1)
        {
            if (character == 32)
            {
                count = count + 1;
            }
        }
        //convert 2 (sentences) to accepted ASCII values
        else if (target == 2)
        {
            if (character == 33 || character == 46 || character == 63)
            {
                count = count + 1;
            }
        }
        i++;
    }
    return count;
}