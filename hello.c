//include headers
#include <stdio.h>
#include <cs50.h>
//define main
int main(void)
{
    //ask for input
    string s = get_string("What is your name? ");
    //print the phrase
    printf("hello, %s\n", s);
}