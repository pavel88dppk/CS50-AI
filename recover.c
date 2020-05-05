#include <stdio.h>
#include <stdlib.h>
//including libraries


int main(int argc, char *argv[])
//checking for valid usage
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
    //setting counter to zero
    int i = 0;
    
    //opening the memory card
    FILE *inptr = fopen(argv[1], "r");
    //if it is empty, return false
    if (inptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open infile");
        return 1;
    }
    //finding memory for 512 bytes
    unsigned char buffer[512];
    //defining the current image and filename
    char filename[10];
    FILE *img;
    
    //reads until it reaches the end of the file
    while (fread(&buffer, 512, 1, inptr)) 
    {
        //chceking for JPG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //set count to += 1
            i++;
            //if it isn't the first image (you couldn't close zeroth image),you have to close the previous
            if (i > 1)
            {
                fclose(img);
            }
            
            //naming the current file
            sprintf(filename, "%03d.jpg", i - 1);
            //open file for writing
            img = fopen(filename, "a");
        }
        //if we do have an open file, write
        if (i >= 1)
        {
            fwrite(&buffer, 512, 1, img);    
        }
        
        //if we have reached the end of the card, close all reamining files
        if (feof(inptr))
        {
            if (buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && (buffer[3] & 0xf0) != 0xe0)
            {
                fclose(img);
                fclose(inptr);
            }
        }
    }
    //return success
    return 0;
}