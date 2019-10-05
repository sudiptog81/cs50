/**
 * PSet 3.1 - Whodunit
 * Written by Sudipto Ghosh for CS50
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char **argv)
{
    // ensure proper usage
    if (argc != 3 || !argv[1] || !argv[2])
    {
        printf("Usage: ./whodunit infile outfile\n");
        return 1;
    }
    
    // store filenames
    char *inFile = argv[1], *outFile = argv[2];
    
    // open input file
    FILE *ifPtr = fopen(inFile, "r");
    if (!ifPtr)
    {
        printf("Input file %s could not be opened\n", inFile);
        return 2;
    }
    
    // open output file
    FILE *ofPtr = fopen(outFile, "w");
    if (!ofPtr)
    {
        fclose(ifPtr);
        printf("Output file %s could not be opened\n", outFile);
        return 3;
    }
    
    // read input bitmap file header
    BITMAPFILEHEADER fileHeader;
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, ifPtr);
    
    // read input bitmap info header
    BITMAPINFOHEADER infoHeader;
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, ifPtr);

    // ensure that input file is a 24-bit BMP file
    if (fileHeader.bfType != 0x4d42 || 
        fileHeader.bfOffBits != 54 || 
        infoHeader.biSize != 40 ||
        infoHeader.biBitCount != 24 || 
        infoHeader.biCompression != 0)
    {
        fclose(ofPtr);
        fclose(ifPtr);
        printf("Input file is in an unsupported file format\n");
        return 4;
    }

    // write output bitmap's file header
    fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, ofPtr);

    // write output bitmap's info header
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, ofPtr);

    // determine padding for scanlines
    int padding = (4 - (infoHeader.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over input bitmap's scanlines
    for (int i = 0, biHeight = abs(infoHeader.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in each scanline
        for (int j = 0; j < infoHeader.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triplet;
            
            // read RGB triplet from input bitmap
            fread(&triplet, sizeof(RGBTRIPLE), 1, ifPtr);

            // change all reddish pixels to white
            if (triplet.rgbtRed >= 0xee)
            {
                triplet.rgbtRed = 0xff;
                triplet.rgbtBlue = 0xff;
                triplet.rgbtGreen = 0xff;
            }
            
            // change all non-white pixels to black
            // for better contrast and readability
            if (triplet.rgbtRed != 0xff &&
                triplet.rgbtBlue != 0xff &&
                triplet.rgbtGreen != 0xff)
            {
                triplet.rgbtRed = 0x00;
                triplet.rgbtBlue = 0x00;
                triplet.rgbtGreen = 0x00;
            }
            
            // write RGB triplet to output bitmap
            fwrite(&triplet, sizeof(RGBTRIPLE), 1, ofPtr);
        }

        // skip over any padding
        fseek(ifPtr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, ofPtr);
        }
    }

    // close all filestreams
    fclose(ifPtr);
    fclose(ofPtr);
    
    return 0;
}
