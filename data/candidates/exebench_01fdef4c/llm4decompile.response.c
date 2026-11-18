void cftb040(picoos_int32 *a)
{
    float x0r, x0i;
    float x1r, x1i;
    float x2r, x2i;
    float x3r, x3i;

    x0r = ((float *)a)[0] - ((float *)a)[4];
    x0i = ((float *)a)[1] - ((float *)a)[5];
    x1r = ((float *)a)[0] + ((float *)a)[4];
    x1i = ((float *)a)[1] + ((float *)a)[5];
    x2r = ((float *)a)[2] - ((float *)a)[6];
    x2i = ((float *)a)[3] - ((float *)a)[7];
    x3r = ((float *)a)[2] + ((float *)a)[6];
    x3i = ((float *)a)[3] + ((float *)a)[7];

    ((float *)a)[0] = x1r + x3r;
    ((float *)a)[1] = x1i + x3i;
    ((float *)a)[2] = x0r - x2i;
    ((float *)a)[3] = x0i + x2r;
    ((float *)a)[4] = x1r - x3r;
    ((float *)a)[5] = x1i - x3i;
    ((float *)a)[6] = x0r + x2i;
    ((float *)a)[7] = x0i - x2r;
}