#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("incorrect key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("incorrect key\n");
            return 1;
        }
    }

   
    int sl = strlen(argv[1]);
    if (sl <= 25)
    {
        printf("incorrect key\n");
        return 1;
    }

  
    int count = 0;
    int cnt = 0;
    for (int i = 0; i < sl; i++)
    {
        for (int N = 0; argv[1][N] != '\0'; N++)
        {
            cnt++;
            if (argv[1][N] == argv[1][i])
            {
                count++;
            }
        }
    }

    if (count != sl)
    {
        printf("incorrect key\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

   
    int txtin = strlen(plaintext);
    for (int q = 0; q < txtin; q++)
    {
        for (int m = 0; m < 26; m++)
        {
            if (plaintext[q] == 'a' + m)
            {
                if (argv[1][m] >= 'a' && argv[1][m] <= 'z')
                {
                    printf("%c", argv[1][m]);
                }
                else
                {
                    char let1 = argv[1][m] + 32;
                    printf("%c", let1);
                    //making it capital
                }
            }
            else if (plaintext[q] == 'A' + m)
            {
               
                if (argv[1][m] >= 'a' && argv[1][m] <= 'q')
                {
                    char let2 = argv[1][m] - 32;
                    printf("%c", let2);
                }
                else
                {
                    printf("%c", argv[1][m]);
                }
            }
        }
        if (!isalpha(plaintext[q]))
        {
            printf("%c", plaintext[q]);
        }
    }
    printf("\n");
}