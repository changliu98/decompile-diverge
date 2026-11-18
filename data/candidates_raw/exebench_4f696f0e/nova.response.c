static void func0(unsigned char *a)
{
    unsigned char t;
    t = a[0];
    a[0] = a[3];
    a[3] = t;
    t = a[1];
    a[1] = a[2];
    a[2] = t;
}