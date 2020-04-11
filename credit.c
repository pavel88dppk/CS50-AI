#include <stdio.h>
#include <cs50.h>
int ndig (string s);
int ndig (string s)
{
    int N = 0;
    
    string number [1];
    number [0]= get_string("Number: ");
    for (int l = 0; l <= N; l++)
    {
        for (int i = 0; i < N; i++)
    {
        printf("%i", number [0][N]);
        N = N + 1;
    }
    printf("%i", N);
    }
}
int main(void)
