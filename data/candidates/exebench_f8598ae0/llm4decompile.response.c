int find(float xt, float *x, int n)
{
    int il, im, ir, itst;

    if (xt <= x[0])
        return 0;
    if (xt >= x[n-1])
        return n-1;

    il = 1;
    ir = n;
    while ((itst = ir - il) > 1) {
        im = (il + ir) / 2;
        if (xt < x[im-1])
            ir = im;
        else
            il = im;
    }
    return il-1;
}