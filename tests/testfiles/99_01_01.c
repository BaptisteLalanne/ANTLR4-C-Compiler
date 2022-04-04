#include <stdio.h>

int main()
{
    int n = 15;

    char a;
    a='A';
    while (a<'A'+n)
    {
        putchar(a);
        a=a+1;
    }
    return a;
}