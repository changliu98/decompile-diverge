void cadd(float *c)
{
 float t0r,t0i,t1r,t1i;

 t0r = c[0];
 t0i = c[1];
 t1r = c[2];
 t1i = c[3];

 t1r = t0r + t1r;
 t1i = t0i + t1i;
 t1r = t0r - t1r;
 t1i = t0i - t1i;

 c[0] = t1r;
 c[1] = t1i;
 c[2] = t1r;
 c[3] = t1i;
}