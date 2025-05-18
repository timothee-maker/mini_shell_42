#include <stdio.h>

int main(void)
{
    char *str = "";
    while (*str)
    {
        printf("%c\n", *str);
        str++;
    }
}