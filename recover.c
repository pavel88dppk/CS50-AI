#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
     if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open card.raw");
        return 1;
    }
    
    // Allocate memory for 512 byte chunks
    unsigned char buffer[512];
    
    // How many jpgs found
    int i = 0;
    
    // Current filename and img
    char title[10];
    FILE* img;
    
    // Read until end of card
    while(fread(&buffer, 512, 1, inptr)) 
    {
        // start of new jpg?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Found jpg
            i++;
            
            // Close prev file (if any)
            if (i > 1)
            {
                fclose(img);
            }
            
            // Open new file and write first buffer
            sprintf(title, "%03d.jpg", i - 1);
            img = fopen(title, "a");
        }
        
        // If currently writing to file, write buffer
        if (i >= 1)
        {
            fwrite(&buffer, 512, 1, img);    
        }
        if (feof(inptr))
        {
            if (buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && (buffer[3] & 0xf0) != 0xe0)
            {
                fclose(img);
                fclose(inptr);
            }
            
        }
    }
    return 0;
}