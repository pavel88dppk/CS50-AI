#include <cs50.h>
#include <stdio.h>


int main(void)
{
    int i = get_int("Height: ");
    for (int g = 0; i < 1 || i > 8; g++)
    {
        if (i < 1 || i > 8)
        {
            i = get_int("Height: "); 
        }
    }

    for (int n = 0; n < i; n++)
    {
        for (int m = 0; m < i; m++)
        {
            if (i - (m + n) > 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        
        for (int m = 0; m < i; m++)
        {
            if (i - (n + m) <= 1)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
