int func0(int a, int b, int c)
{
    char t;
    if ((a != b) && (b != c) && (c != a))
 t = 1;
    else
 t = 0;

    return (t & 1);
}