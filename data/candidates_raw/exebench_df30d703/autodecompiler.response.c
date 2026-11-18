float getPixelExtend(image im, int x, int y, int c)
{
    assert__bench(x < im.w && y < im.h && c < im.c);
    if(x < 0) x = 0;
    if(x >= im.w) x = im.w-1;
    if(y < 0) y = 0;
    if(y >= im.h) y = im.h-1;
    return get_pixel(im, x, y, c);
}