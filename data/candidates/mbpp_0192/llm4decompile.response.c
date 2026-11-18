int func0(char *str)
{
    int c1 = 0;
    int c2 = 0;
    while (*str) {
        if ((*__ctype_b_loc ())[(int) ((unsigned char) *str)] & 0x400)
            c1 = 1;
        if ((*__ctype_b_loc ())[(int) ((unsigned char) *str)] & 0x800)
            c2 = 1;
        ++str;
    }
    return c1 && c2;
}