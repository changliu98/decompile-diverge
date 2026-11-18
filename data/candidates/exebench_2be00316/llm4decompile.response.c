void ZVdotU31(int n, double y0[], double y1[], double y2[], double x[], double sums[])
{
    double xr,xi;
    double yr0,yi0,yr1,yi1,yr2,yi2;
    double r00,r10,r20,i00,i10,i20;
    int rloc,iloc,ii;

    r00 = 0.0;
    i00 = 0.0;
    r10 = 0.0;
    i10 = 0.0;
    r20 = 0.0;
    i20 = 0.0;
    rloc = 0;
    iloc = 1;
    for (ii=0;ii<n;ii++) {
 xr = x[rloc];
 xi = x[iloc];
 yr0 = y0[rloc];
 yi0 = y0[iloc];
 yr1 = y1[rloc];
 yi1 = y1[iloc];
 yr2 = y2[rloc];
 yi2 = y2[iloc];
 r00 += (yr0*xr-yi0*xi);
 i00 += (yi0*xr+yr0*xi);
 r10 += (yr1*xr-yi1*xi);
 i10 += (yi1*xr+yr1*xi);
 r20 += (yr2*xr-yi2*xi);
 i20 += (yi2*xr+yr2*xi);
 rloc += 2;
 iloc += 2;
    }
    sums[0] = r00;
    sums[1] = i00;
    sums[2] = r10;
    sums[3] = i10;
    sums[4] = r20;
    sums[5] = i20;
}