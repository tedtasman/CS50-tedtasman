#include <cs50.h>
#include <stdio.h>

void spaces(int row, int height);
void hashes(int row);

int main(void)
{
    int height;
    //find pyramid height
    do
    {
        height = get_int("How Tall? ");
    }
    while (height < 1 || height > 8);
    //for every row
    for (int row = 1; row <= height; row++)
    {
        //print spaces
        spaces(row, height);
        //print first half
        hashes(row);
        //gap
        printf("  ");
        //print second half
        hashes(row);
        //new line
        printf("\n");
    }
}

//spaces loop
void spaces(int row, int height)
{
    //number of spaces = height - current row
    for (int space = 0; space < height - row; space++)
    {
        printf(" ");
    }
}

//hashes loop
void hashes(int row)
{
    //number of hashes = current row
    for (int hash = 0; hash < row; hash++)
    {
        printf("#");
    }
}