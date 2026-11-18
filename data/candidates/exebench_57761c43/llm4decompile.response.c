void char_replace(char *str, char origc, char newc)
{
    while (*str) {
        if (*++str == origc)
            *str = newc;
    }
}