void si_swapl(int *x)
{
    union {
        int i;
        unsigned char c[sizeof(int)];
    } u;

    u.i = *x;
    { unsigned char t = u.c[0]; u.c[0] = u.c[3]; u.c[3] = t; };
    { unsigned char t = u.c[1]; u.c[1] = u.c[2]; u.c[2] = t; };

    *x = u.i;
}