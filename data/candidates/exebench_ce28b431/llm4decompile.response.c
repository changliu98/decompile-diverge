void swap_int(int *i)
{
    unsigned char *c = (unsigned char *)i;
    unsigned char t;
    t = c[0]; c[0] = c[3]; c[3] = t;
    t = c[1]; c[1] = c[2]; c[2] = t;
}