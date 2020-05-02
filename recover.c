#include <stdio.h>
#include <stdlib.h>
typedef uint8_t byte;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }
    char *infile = argv[1]
    FILE *inpointer = fopen(argv[0], "r");
    if (inpointer == NULL)
    {
        printf("Could not open")
        return 1;
    }
    byte buffer[512]
    int i = 0;
    for (int n = 0; n < memory; n++)
    {
        if (buffer[n][1] == 0xff && buffer[n][1] = 0xd8 && buffer[n][2] = 0xff && buffer[n][2] = 0xe0)
        {
            i++;
            sprintf( filename ,"03i.jpg", i)
            fread(buffer, sizeof byte, 512, inpointer);
            
        }
    }
    
}
