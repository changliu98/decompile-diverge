void h(int *x, int y)
{

    if (*x > y)
        h(x, *x);
    else
        *x = *x - y;

}