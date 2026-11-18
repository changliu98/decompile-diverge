void dstsub4(int n,float *a)
{
    float xr,xi,wr,wi,wdr,wdi,wkr,wki;

    n >>= 1;
    if (n == 2) {
        xr = a[1];
        xi = a[3];
        wr = 0.5*0.5;
        wi = -(0.5*0.5);
        wdr = 0.5*xr + wi*xi;
        wdi = 0.5*xi + wr*xr;
        wkr = 0.5*xr + wi*xi;
        wki = -(0.5*xi) + wr*xr;
        a[1] = wdr;
        a[3] = wki;
    }
    a[n] *= 0.5;
}