float map(int x, int in_min, int in_max, float out_min, float out_max)
{
 double output;
 output = (x - in_min) * (out_max - out_min) / (in_max - in_min) * 1.0 + out_min;
 return output;
}