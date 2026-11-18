float map(int x, int in_min, int in_max, float out_min, float out_max)
{
 double k = (double)(out_max - out_min) / (double)(in_max - in_min);
 double y = (double)out_min + (double)(x - in_min) * k;
 return (float)y;
}