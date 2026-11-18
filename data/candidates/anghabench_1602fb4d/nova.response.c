static int mode1112(int r, int g, int b, int c0, int c1, int c2, int c3)
{
    int y;
    y = (r*4 + g*2 + b)<<1;
    y += (c0+c1+c2+c3);
    y = (y+8)>>4;
    return y;
}