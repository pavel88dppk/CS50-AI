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
        printf("Usage: ./recover infile\n");
        return 1;
    }
    
    char *infile = argv[1];
    FILE *inpointer = fopen(argv[1], "r");
    int i = 0;
    
    if (inpointer == NULL)
    {
        printf("Could not open");
        return 1;
    }
    
    byte buffer[512];
    
    
    FILE *img;
    char* filename[9];
    
    while (true)
    {    
        size_t alreadyread = fread(buffer, sizeof(byte), 512, inpointer);
        
        if (alreadyread == 0 && feof(inpointer))
        {
            break;
        }
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            i++;
            if (i > 1)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", i);
            img = fopen (filename, "w");
        }
            
        if (img != NULL)
            {
                fwrite(buffer, sizeof (byte), alreadyread, inpointer);
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
