#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define NULL ((void*)0)
typedef uint8_t byte;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }
    
    char *infile = argv[1];
    FILE *inpointer = fopen(infile, "r");
    int i = 0;
    
    if (inpointer == NULL)
    {
        fclose(inpointer);
        fprintf(stderr, "Could not open");
        return 1;
    }
    
    byte buffer[512];
    
    
    FILE *img;
    char* filename = NULL;
    
    while (fread(&buffer, 512, 1, inpointer))
    {    
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            i++;
            if (i > 1)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", i - 1);
            img = fopen (filename, "a");
        }
            
        if (i >= 1)
            {
                fwrite(&buffer, 512, 1, inpointer);
            }
    }
    if (feof(inpointer))
    {
        if (buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff || (buffer[3] & 0xf0) != 0xe0)
        {
            fclose(img);
            fclose(inpointer);
        }
    }
    return 0;
}
