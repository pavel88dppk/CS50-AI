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
    
    
    FILE *outpointer = NULL;
    char* filename = NULL;
    
    
    if (feof(inpointer))
    {
        fclose(outpointer);
    }
    
    while (true)
    {    
        size_t alreadyread = fread(buffer, sizeof (byte), 512, inpointer);
        
        if (alreadyread == 0 && feof(inpointer))
        {
            break;
        }
        fread(buffer, sizeof (byte), 512, inpointer);
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && outpointer != NULL)
        {
            i++;
            fclose(outpointer);
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf( filename, "%03i.jpg", i);
            outpointer = fopen (filename, "w");
        }
            
        if (outpointer != NULL)
            {
                fwrite(buffer, sizeof (byte), 512, inpointer);
            }
    }
    if (feof(inpointer))
    {
        if (buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff || (buffer[3] & 0xf0) != 0xe0)
        {
            fclose(outpointer);
            fclose(inpointer);
        }
    }
    return 0;
}
