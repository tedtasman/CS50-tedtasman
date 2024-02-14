#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512

FILE * makefile(int count, char *filename);

int main(int argc, char *argv[])
{
    // check for proper usage
    if (argc == 2)
    {
        // open file
        FILE *image = fopen(argv[1], "r");
        // regect null file
        if (image == NULL)
        {
            printf("File %s cannot be opened\n", argv[1]);
            return 1;
        }
        // allocate 512 byte buffer
        unsigned char buffer[512];
        // initialize count
        int count = 0;
        // allocate memory for filename
        char *filename = malloc(8);
        // initialize openfile
        FILE *openfile;
        // repeat for whole card (until fread returns less than 512 bytes)
        while (fread(buffer, 1, BLOCK_SIZE, image) == BLOCK_SIZE)
        {
            // check if jpeg header
            if (buffer[0] == 0xFF && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // check if this is the first jpeg
                if (count == 0)
                {
                    // get new file
                    openfile = makefile(count, filename);
                    // increase jpeg count
                    count++;
                    // write to jpeg file
                    fwrite(buffer, 1, BLOCK_SIZE, openfile);
                }
                // else open new jpeg and write to it
                else
                {
                    // close old file
                    fclose(openfile);
                    // get new file
                    openfile = makefile(count, filename);
                    // increase jpeg count
                    count++;
                    // write to jpeg file
                    fwrite(buffer, 1, BLOCK_SIZE, openfile);
                }
            }
            // else write to open jpeg
            else
            {
                fwrite(buffer, 1, BLOCK_SIZE, openfile);
            }
        }
        // close files
        fclose(openfile);
        fclose(image);
        // free memory
        free(filename);
    }
    else
    {
        // regect improper usage
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

}

FILE * makefile(int count, char *filename)
{
    // create jpeg filename
    sprintf(filename, "%03i.jpg", count);
    // open new jpeg file
    FILE *new = fopen(filename, "w");
    return new;
}