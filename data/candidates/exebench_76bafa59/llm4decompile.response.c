void rifft1pt(float *ioptr,float scale)
{
float xi,xr,yi,yr;

xr=ioptr[0];
xi=ioptr[1];

yr=scale*(xr+xi);
yi=scale*(xr-xi);

ioptr[0]=yr;
ioptr[1]=yi;
}