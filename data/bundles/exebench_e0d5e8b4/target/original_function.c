void dstsub4(int n, float *a)
{
    int m;
    float wki, wdr, wdi, xr;

    wki = ((float) 0.707106781186547524400844362104849039284835937688);
    m = n >> 1;
    if (m == 2) {
        wdr = wki * ((float) 0.382683432365089771728459984030398866761344562485);
        wdi = wki * ((float) 0.923879532511286756128183189396788286822416625863);
        xr = wdi * a[3] - wdr * a[1];
        a[3] = wdr * a[3] + wdi * a[1];
        a[1] = xr;
    }
    a[m] *= wki;
}