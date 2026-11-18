#include <stdlib.h>

#include <string.h>

#include <wctype.h>

void
utf8_int_string (unsigned int unicode_value, char *string)
{
    if (!string)
        return;

    string[0] = '\0';

    if (unicode_value <= 0x007F)
    {

        string[0] = unicode_value;
        string[1] = '\0';
    }
    else if (unicode_value <= 0x07FF)
    {

        string[0] = 0xC0 | ((unicode_value >> 6) & 0x1F);
        string[1] = 0x80 | (unicode_value & 0x3F);
        string[2] = '\0';
    }
    else if (unicode_value <= 0xFFFF)
    {

        string[0] = 0xE0 | ((unicode_value >> 12) & 0x0F);
        string[1] = 0x80 | ((unicode_value >> 6) & 0x3F);
        string[2] = 0x80 | (unicode_value & 0x3F);
        string[3] = '\0';
    }
    else if (unicode_value <= 0x1FFFFF)
    {

        string[0] = 0xF0 | ((unicode_value >> 18) & 0x07);
        string[1] = 0x80 | ((unicode_value >> 12) & 0x3F);
        string[2] = 0x80 | ((unicode_value >> 6) & 0x3F);
        string[3] = 0x80 | (unicode_value & 0x3F);
        string[4] = '\0';
    }
}
