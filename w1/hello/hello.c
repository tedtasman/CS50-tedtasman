#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //asks name and then responds with "hello, name"
    printf("hello, %s \n", get_string("What's your name? "));
}