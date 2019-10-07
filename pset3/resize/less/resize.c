/**
 * PSet 3.2a - Resize - Less Comfortable
 * Written by Sudipto Ghosh for CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char **argv)
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // extract parameters from args
    int factor = atoi(argv[1]);
    char *ifFile = argv[2];
    char *ofFile = argv[3];

    // ensure factor is valid
    if (factor > 100 || factor < 1)
    {
        printf("Factor should be in the range of [1, 100]\n");
        return 1;
    }

    // open input bitmap file
    FILE *ifPtr = fopen(ifFile, "r");
    if (!ifPtr)
    {
        printf("Input file cannot be opened\n");
        return 1;
    }

    // open output bitmap file
    FILE *ofPtr = fopen(ofFile, "w");
    if (!ofPtr)
    {
        fclose(ifPtr);
        printf("Output file cannot be opened\n");
        return 1;
    }

    // read input bitmap's file header
    BITMAPFILEHEADER bfOld, bfNew;
    fread(&bfOld, sizeof(BITMAPFILEHEADER), 1, ifPtr);
    bfNew = bfOld;

    // read input bitmap's info header
    BITMAPINFOHEADER biOld, biNew;
    fread(&biOld, sizeof(BITMAPINFOHEADER), 1, ifPtr);
    biNew = biOld;

    // ensure input is 24-bit uncompressed bitmap
    if (bfOld.bfType != 0x4d42 ||
        bfOld.bfOffBits != 54 ||
        biOld.biSize != 40 ||
        biOld.biBitCount != 24 ||
        biOld.biCompression != 0)
    {
        fclose(ofPtr);
        fclose(ifPtr);
        printf("Input file is in an unsupported format\n");
        return 2;
    }

    // scale width and height info
    biNew.biWidth *= factor;
    biNew.biHeight *= factor;

    // determine padding for scanlines and size of old image
    int paddingOld = (4 - (biOld.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for scanlines and size of new image
    int paddingNew = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate image and file size of output
    biNew.biSizeImage = ((sizeof(RGBTRIPLE) * biNew.biWidth) + paddingNew) * abs(biNew.biHeight);
    bfNew.bfSize = biNew.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write output bitmap's file header
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, ofPtr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, ofPtr);

    if (factor > 1)
    {
        // iterate over input bitmap's scanlines
        for (int i = 0; i < abs(biOld.biHeight); i++)
        {
            // resizing vertically
            for (int j = 0; j < factor; j++)
            {
                // iterate over pixels in scanline
                for (int k = 0; k < biOld.biWidth; k++)
                {
                    // temporary storage
                    RGBTRIPLE triplet;

                    // read RGB triplet from input file
                    fread(&triplet, sizeof(RGBTRIPLE), 1, ifPtr);

                    // resizing horizontally
                    for (int l = 0; l < factor; l++)
                    {
                        // write RGB triplet to output file
                        fwrite(&triplet, sizeof(RGBTRIPLE), 1, ofPtr);
                    }
                }

                // skip over padding in the input file
                fseek(ifPtr, paddingOld, SEEK_CUR);

                // add the padding to output file
                for (int m = 0; m < paddingNew; m++)
                {
                    fputc(0x00, ofPtr);
                }

                // keep i/p scanline same for o/p scanlines
                if (j < factor - 1)
                {
                    // move back cursor to the start of current
                    // scanline of the input bitmap file
                    long cursor = biOld.biWidth * sizeof(RGBTRIPLE) + paddingOld;
                    fseek(ifPtr, -cursor, SEEK_CUR);
                }
            }
        }
    }
    else if (factor == 1)
    {
        // iterate over input bitmap's scanlines
        for (int i = 0; i < abs(biOld.biHeight); i++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < biOld.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triplet;

                // read RGB triplet from input file
                fread(&triplet, sizeof(RGBTRIPLE), 1, ifPtr);

                // write RGB triplet to output file
                fwrite(&triplet, sizeof(RGBTRIPLE), 1, ofPtr);
            }

            // skip over padding in the input file
            fseek(ifPtr, paddingOld, SEEK_CUR);

            // add the padding to output file
            for (int m = 0; m < paddingNew; m++)
            {
                fputc(0x00, ofPtr);
            }
        }
    }

    // close infile
    fclose(ifPtr);

    // close outfile
    fclose(ofPtr);

    return 0;
}