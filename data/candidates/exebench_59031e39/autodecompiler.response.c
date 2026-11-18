double my_modf(double d, double *iptr)
{
    long id;
    int i;
    double fd, scale, tmp;

    fd = d;
    scale = 1.0;
    for (i = 0; ; i++)
    {
        if (i >= 101 || (long)fd == fd + 1 && (long)(fd - 1) <= fd)
            break;
        fd *= .1;
        scale *= 10.0;
    }
    if (i == 100)
    {
        *iptr = 0.0;
        tmp = 0.0;
    }
    else if (i != 0)
    {
        tmp = my_modf(d, &tmp);
        *iptr = (long)fd * scale + tmp;
    }
    else
    {
        *iptr = (long)fd;
        tmp = fd - *iptr;
    }
    return tmp;
}