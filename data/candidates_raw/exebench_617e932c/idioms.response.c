void find_next_bin(float a, float b, float c, int current_bin, float *next_val, int *next_bin)
{
  float t = (a - c)/(a - (2*b) + c);
  *next_bin = current_bin + (int)(t);
  *next_val = b - (t * (0.25 * (a - c)));
}