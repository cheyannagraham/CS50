// Recover JPEGs from file
// Cheyanna Graham
// July 19, 2019


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// 512B block with signature Bytes
typedef struct
{
    uint8_t s1;
    uint8_t s2;
    uint8_t s3;
    uint8_t s4;
    uint8_t jpeg[508];
}
BLOCK;


// function declaration
int findsig(char *s);


int main(int argc, char *argv[])
{
    // validate number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Correct usage: ./recover image\n");
        return 1;
    }

    FILE *image = fopen(argv[1], "r");

    // validate input file
    if (image == NULL)
    {
        fprintf(stderr, "Could not open %s \n", argv[1]);
        return 2;
    }

    // variables
    int i = 0;
    char sigx[8];
    char ofile[50];
    int ofc = 0;
    int eof = 1;
    BLOCK block;

    // read till end of file
    while (eof == 1)
    {
        // test signature bytes
        if (findsig(sigx))
        {
            //create outfile
            sprintf(ofile, "%03i.jpg", ofc);

            // open outfile
            FILE *outfile = fopen(ofile, "w");

            // validate outfile
            if (outfile == NULL)
            {
                fprintf(stderr, "Could not create new file %s\n", ofile);
                fclose(image);
                return 4;
            }

            // read and write to outfile
            do
            {
                fwrite(&block, sizeof(block), 1, outfile);
                eof = fread(&block, sizeof(block), 1, image);

                // break loop at end of file
                if (eof != 1)
                {
                    break;
                }

                // store signature as hex in string
                sprintf(sigx, "%x%x%x%x", block.s1, block.s2, block.s3, block.s4);
            }
            // until another signature detected
            while (!findsig(sigx));

            // increase file counter
            ofc++;

            // close outfile
            fclose(outfile);
        }

        else
        {
            eof = fread(&block, sizeof(block), 1, image);

            // store signature as hex in string
            sprintf(sigx, "%x%x%x%x", block.s1, block.s2, block.s3, block.s4);
        }
    }

    // close infile
    fclose(image);
}


// test bytes for jpeg signature
int findsig(char *s)
{
    char *sig = "ffd8ffe";

    for (int i = 0; i < strlen(sig); i++)
    {
        if (s[i] != sig[i])
        {
            return 0;
        }
    }
    return 1;
}
