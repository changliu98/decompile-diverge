float __cdecl map(int x, int in_min, int in_max, float out_min, float out_max)
{
  return 1.0 * (float)(out_max - out_min) / (double)(in_max - in_min) * (double)(x - in_min) + out_min;
}