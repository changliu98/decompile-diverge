int triangle(int a, int b, int c)
{
    char t;
    if ((a+b <= c) || (a+c <= b) || (b+c <= a))
 t = 0;
    else
 t = 1;

    return (t & 1);
}