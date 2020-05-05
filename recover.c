#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
     if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
    
    int i = 0;
    
    
    FILE* inptr = fopen(argv[1], "r");
    
    if (inptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open infile");
        return 1;
    }
    
    unsigned char buffer[512];
    char filename[10];
    FILE* img;
    
    while(fread(&buffer, 512, 1, inptr)) 
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            i++;
            
            if (i > 1)
            {
                fclose(img);
            }
            
            sprintf(filename, "%03d.jpg", i - 1);
            img = fopen(filename, "a");
        }
        
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