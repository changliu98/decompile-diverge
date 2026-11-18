float KBND_REPLICATE(float *img,int w,int h,int x,int y,float bnd_const)
{
    if (x<0) x=0;
    if (x>=w) x=w-1;
    if (y<0) y=0;
    if (y>=h) y=h-1;
    return img[y*w+x];
}