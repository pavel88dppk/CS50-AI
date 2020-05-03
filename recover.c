#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
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
    FILE *inpointer = fopen(argv[0], "r");
    if (inpointer == NULL)
    {
        printf("Could not open");
        return 1;
    }
    byte buffer[512];
    int i = 0;
    char* filename = NULL;
    FILE *outpointer = NULL;
    while (&free)
    {       
        fread(buffer, sizeof (byte), 512, inpointer);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (feof(inpointer))
            {
                fclose(outpointer);
            }
            i++;
            sprintf( filename, "%03i.jpg", i);
            outpointer = fopen (filename, "w");
            
        }
        if (outpointer != NULL)
            {
                fwrite(buffer, sizeof (byte), 512, inpointer);
            }
        
    }
    
}
