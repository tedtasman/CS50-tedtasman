#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n;
    do
    {
        n = get_int("Initial Population: ");
    }
    while (n < 9);
    // TODO: Prompt for end size
    int f;
    do
    {
        f = get_int("Final Population: ");
    }
    while (f <= n);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (n < f)
    {
        n = n + n / 3 - n / 4;
        years++;
    }
    // TODO: Print number of years
    printf("Number of Years: %i \n", years);
}
