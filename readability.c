#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//including all necessary libraries

int main(void)
{
    int N = 0;
    string s [1];
    s [0] = get_string("Text: ");
    //we want to accept the text form user
    double count = 0;
    int l = strlen(s [0]);
    //counting symbols
    for (int i = 0; i < l; i++)
    {
        int f = s [0][N];
        if (f >= 65 && f <= 90)
        {
            count += 1;
        }
        else if (f >= 97 && f <= 122)
            //if the char it investigates is a letter, it grows the symbol rate
        {
            count += 1;
        }
        N = N + 1;
        f = 0;
    }
    N = 0;
    double wc = 0;
    //counting words
    for (int i = 0; i < l; i++)
    {
        int f = s [0][N];
        if (f >= 65 && f <= 90)
        {
            wc += 0;
        }
        else if (f >= 97 && f <= 122)
        {
            wc += 0;
        }
        else if (f == 39)
        {
            wc += 0;
        }
        else if (f == 45)
        {
            wc += 0;
            f = s [0][N - 1];
            if (f >= 65 && f <= 90)
            {
                wc += 0;
            }
            else if (f >= 97 && f <= 122)
            {
                wc += 0;
            }
            else
            {
                wc += 1;
            }
        }
        else
        {
            wc += 1;
            f = s [0][N - 1];
            if (f >= 65 && f <= 90)
            {
                wc += 0;
            }
            else if (f >= 97 && f <= 122)
            {
                wc += 0;
            }
            else
            {
                wc -= 1;
            }
        }
        N = N + 1;
        f = 0;
    }
    double sc = 0;
    N = 0;
    //counting sentances

    for (int i = 0; i < l; i++)
    {
        int f = s [0][N];
        if (f >= 65 && f <= 90)
        {
            sc += 0;
        }
        else if (f >= 97 && f <= 122)
        {
            sc += 0;
        }
        else if (f == 33)
        {
            sc += 1;
        }
        else if (f == 46)
        {
            sc += 1;
        }
        else if (f == 63)
        {
            sc += 1;
        }
        else
        {
            sc += 0;
        }
        N = N + 1;
        f = 0;

    }
    double L = (count * (100 / wc));
    double S = (sc * (100 / wc));
    float index = ((0.0588 * L) - (0.296 * S) - 15.8);
    //putting everything together
    //substitution in the formula
    index = (round(index));
    //rounding index


    if (index <= 1.5)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 15.5)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
    //saying which grade it belongs to
}