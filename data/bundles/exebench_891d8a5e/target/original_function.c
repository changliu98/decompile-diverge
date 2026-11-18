void decdms(double dec, int *d, int *m, float *s)

{double temp;
 int itemp;
 temp = dec; itemp = (int)temp; *d = itemp;
 temp = temp - (double)itemp;
 if (temp<0.0) temp = -temp;
 temp = temp*60.0; itemp = (int)temp; *m = itemp;
 temp = temp - (double)itemp;
 temp = temp*60.0; *s = (float)temp;
}