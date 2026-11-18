static void rgb2hsv(double r, double g, double b,
  double *h, double *s, double *v)
{

    double rgbmin, rgbmax;
    double rc, bc, gc;
    double ht = 0.0, st = 0.0;

    rgbmin = ((r)<(((g)<(b)?(g):(b)))?(r):(((g)<(b)?(g):(b))));
    rgbmax = ((r)>(((g)>(b)?(g):(b)))?(r):(((g)>(b)?(g):(b))));

    if (rgbmax > 0.0)
 st = (rgbmax - rgbmin) / rgbmax;

    if (st > 0.0) {
 rc = (rgbmax - r) / (rgbmax - rgbmin);
 gc = (rgbmax - g) / (rgbmax - rgbmin);
 bc = (rgbmax - b) / (rgbmax - rgbmin);
 if (r == rgbmax)
     ht = bc - gc;
 else if (g == rgbmax)
     ht = 2 + rc - bc;
 else if (b == rgbmax)
     ht = 4 + gc - rc;
 ht = ht * 60.0;
 if (ht < 0.0)
     ht += 360.0;
    }
    *h = ht / 360.0;
    *v = rgbmax;
    *s = st;
}