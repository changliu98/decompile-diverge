#include <stdio.h>

void reverse(char *str)
{
    int length = 0;

    while (str[length] != '\0') length++;
    for (int i = 0; i < length / 2; i++)
    {
        char tmp = str[i];
        str[i] = str[length-i-1];
        str[length-i-1] = tmp;
    }
}
