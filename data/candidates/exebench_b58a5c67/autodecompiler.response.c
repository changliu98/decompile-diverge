void r2d (double *ra, double *dec, int *h, double *m, char *s, int *d, double *sec)
{
 float hour;
 float deg;
 float rad = .017453292519943295769;

 *h = (int) ((*ra / rad) / 15.0);
 *m = (int) ((hour = (*ra / rad) / 15.0 - *h) * 60.0);
 *m += 0.000001;
 if (*m >= 60) {
     *m -= 60;
     *h += 1;
 }
 if (*h >= 24)
     *h -= 24;
 if (*dec < 0) {
     *s = '-';
     *dec = -*dec;
 }
 else
     *s = '+';
 *d = (int) (*dec / rad);
 *sec = (*dec / rad - *d) * 60.0;
}