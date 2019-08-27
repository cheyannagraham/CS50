// Resize a BMP file (More)
// Cheyanna Graham
// July 15, 2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: size orig new\n");
        return 1;
    }

    // get resize factor
    float resfactor = atof(argv[1]);

    if (resfactor < 0 || resfactor > 100)
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
    BITMAPFILEHEADER ibf, obf;
    fread(&ibf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER ibi, obi;
    fread(&ibi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (ibf.bfType != 0x4d42 || ibf.bfOffBits != 54 || ibi.biSize != 40 ||
        ibi.biBitCount != 24 || ibi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // copy iheaders to oheaders
    obi = ibi;
    obf = ibf;

    // calc infile padding
    int ipadding = (4 - (ibi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calc outfile height & width
    obi.biWidth = ibi.biWidth * resfactor;
    obi.biHeight = ibi.biHeight * resfactor;

    // calc outfile padding
    int opadding = (4 - (obi.biWidth  * sizeof(RGBTRIPLE)) % 4) % 4;

    // calc outfile size
    int height = labs(obi.biHeight);
    obf.bfSize = ((height * obi.biWidth) * 3) + (opadding * height) + 54;
    obi.biSizeImage = obf.bfSize - 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&obf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&obi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // make image smaller
    if (resfactor < 1)
    {
        // calc pixels and scanlines to decrease by
        int decby = round(ibi.biWidth / (ibi.biWidth * resfactor));

        // calc scanline bytes
        long iwidth = ibi.biWidth * 3 + ipadding;

        // add scanlines to outfile
        for (int i = 0, biHeight = abs(obi.biHeight); i < biHeight; i++)
        {
            // add pixels to scanline
            for (int j = 0, biWidth = obi.biWidth; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                // skip pixels
                for (int k = 1; k < decby; k++)
                {
                    fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                }
            }

            // skip over padding, if any
            fseek(inptr, ipadding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < opadding; k++)
            {
                fputc(0x00, outptr);
            }

            // skip scanlines
            for (int k = 1; k < decby; k++)
            {
                fseek(inptr, iwidth, SEEK_CUR);
            }
        }
    }

    // make imager larger
    else
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(ibi.biHeight); i < biHeight; i++)
        {
            //get file position to reread scan lines
            long fpos = ftell(inptr);

            // add additional scanlines
            for (int l = 0; l < resfactor; l++)
            {
                //move to beginning of scanline
                fseek(inptr, fpos, SEEK_SET);

                // iterate over pixels in scanline
                for (int j = 0; j < ibi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write additional pixels to file
                    for (int k = 0; k < resfactor; k++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip over padding, if any
                fseek(inptr, ipadding, SEEK_CUR);

                // then add it back (to demonstrate how)
                for (int k = 0; k < opadding; k++)
                {
                    fputc(0x00, outptr);
                }
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