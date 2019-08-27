// Resize a BMP file
// Cheyanna Graham
// July 10, 2019

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy orig new\n");
        return 1;
    }
    
    // get resize factor
    int resfactor = atoi(argv[1]);
    
    if (resfactor < 1 || resfactor > 100)
    {
        printf("Please enter a number beween 1 and 100.\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // calc old padding for scanlines
    int oldpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // set new height & width
    bi.biWidth *= resfactor;
    bi.biHeight *= resfactor;
    
    // calc new padding for scanlines
    int newpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // calc new file size
    int height = abs(bi.biHeight);
    bf.bfSize = ((height * bi.biWidth) * 3) + (newpadding * height) + 54;
    bi.biSizeImage = bf.bfSize - 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight / resfactor); i < biHeight; i++)
    {
        //get file position to reread scan lines
        long fpos = ftell(inptr);
        
        // write scanlines resfactor times
        for (int l = 0; l < resfactor; l++)
        {
            //move to beginning of scanline
            fseek(inptr, fpos, SEEK_SET);
            
            // iterate over pixels in scanline
            for (int j = 0, biWidth = bi.biWidth / resfactor; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile resfactor times
                for (int k = 0; k < resfactor; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, oldpadding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}