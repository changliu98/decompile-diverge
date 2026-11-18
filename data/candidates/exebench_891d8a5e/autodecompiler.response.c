void
decdms(double time, int *hour, int *min, float *sec)
{
 double tmp;

 tmp = time;
 *hour = (int)tmp;
 tmp -= *hour;
 tmp *= 60.0;
 *min = (int)tmp;
 tmp -= *min;
 tmp *= 60.0;
 *sec = (float)tmp;
}