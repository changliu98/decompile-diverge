#include <stdarg.h>

static void _prtX16(
    long num,
    char *str
  )
{
    int i;
    char temp[9];

    temp[0] = '\0';
    for (i = 1; i <= 8; i++)
    {
        temp[i] = "0123456789ABCDEF"[num & 0x0F];
        num = num >> 4;
    }
    for (i = 8; temp[i] == '0'; i--);
    if (i == 0)
        i++;
    while (i >= 0)
        *str++ = temp[i--];
}
