/**
 * PSet 3.3 - Recover
 * Written by Sudipto Ghosh for CS50
 */

#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512
#define FILENAME_SIZE 8

int main(int argc, char **argv)
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover rawfile\n");
        return 1;
    }

    // open RAW input file in read mode
    FILE *ifPtr = fopen(argv[1], "r");
    if (!ifPtr)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        fclose(ifPtr);
        return 1;
    }

    // allocate memory to store filenames
    // and hexadecimal data of JPEG block
    char *filename = malloc(FILENAME_SIZE);
    unsigned char block[BLOCK_SIZE] = {'\0'};

    // declare file pointer for JPEG files
    FILE *ofPtr;

    // iterate over each block of the RAW input file
    for (int i = 0; fread(&block, BLOCK_SIZE, 1, ifPtr);)
    {
        // start new file if JPEG signature is detected
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            block[3] >> 4 == 0xe)
        {
            // close previously opened JPEG file
            if (i)
            {
                fclose(ofPtr);
            }

            // compose filename for next JPEG file
            sprintf(filename, "%03d.jpg", i);

            // open the JPEG file for writing data
            ofPtr = fopen(filename, "w");
            if (!ofPtr)
            {
                fprintf(stderr, "Could not write to %s\n", filename);
                fclose(ofPtr);
                fclose(ifPtr);
                return 1;
            }

            // increment file counter after writing
            i++;
        }

        // keep writing if currently writing to file
        if (i)
        {
            // write the block to the JPEG file
            fwrite(&block, BLOCK_SIZE, 1, ofPtr);
        }
    }

    // close latest JPEG file
    fclose(ofPtr);

    // close RAW input file
    fclose(ifPtr);

    // free allocated memory
    free(filename);

    return 0;
}