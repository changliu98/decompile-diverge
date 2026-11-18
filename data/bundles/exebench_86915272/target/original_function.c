void rahms(double ra, int *h, int *m, float *s)

{double temp;
 int itemp;
 temp = ra; if (temp<0.0) temp = temp + 360.0;
 if (temp>360.0) temp = temp - 360.0;
 temp =temp / 15.0; itemp = (int)temp; *h = itemp;
 temp = temp - (double)itemp;
 temp = temp*60.0; itemp = (int)temp; *m = itemp;
 temp = temp - (double)itemp;
 temp = temp*60.0; *s = (float)temp;
}