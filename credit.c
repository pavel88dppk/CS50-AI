#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long input;

    do
    {
        input = get_long_long("Number: ");
    }
    while (input < 0);

    int n1;
    int n2;
    int sumn1;
    int sumproducts;

    sumn1 = 0;
    sumproducts = 0;

    long long numtest = input;
    long long numtest2 = input;
    while (numtest > 1)
    {
        n1 = numtest % 10;
        sumn1 += n1;
        numtest -= n1;
        numtest /= 10;
        n2 = numtest % 10;
        int n22 = n2 * 2;
        if ((n22) > 9)
        {
            sumproducts += n22 % 10;
            sumproducts += (n22 - (n22 % 10)) / 10;
        }
        else
        {
            sumproducts += n22;
        }

        numtest -= n2;
        numtest /= 10;
    }
    if ((sumn1 + sumproducts) % 10 == 0)
    {
        bool amex, master_card, visa;

        amex = (numtest2 >= 340000000000000 && numtest2 < 350000000000000) || (numtest2 >= 370000000000000 && numtest2 < 380000000000000);
        master_card = (numtest2 >= 5100000000000000 && numtest2 < 5600000000000000);
        visa = (numtest2 >= 4000000000000 && numtest2 < 5000000000000) || (numtest2 >= 4000000000000000 && numtest2 < 5000000000000000);
   
        if (amex)
        {
            printf("valid amex\n");
        }
        else if (master_card)
        {
            printf("valid Master card\n");
        }
        else if (visa)
        {
            printf("valid visa\n");
        }
        else
        {
            printf("invalid card\n");
        }
    }   
    else
    {
        printf("invalid card\n");
    }

}
