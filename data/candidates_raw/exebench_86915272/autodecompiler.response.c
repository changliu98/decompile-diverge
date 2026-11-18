void
dec2dms(double dec, int *deg, int *min, float *sec)
{
 double d;

 if ((d = dec) < 0)
     d += 360;
 if (d > 360)
     d -= 360;

 *deg = (int)(d / 15);
 d = (d / 15) - *deg;
 d *= 60;
 *min = (int)d;
 d = d - *min;
 d *= 60;
 *sec = (float)d;
}