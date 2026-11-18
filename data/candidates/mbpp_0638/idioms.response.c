int func0(int temp, int wind)
{
  return (int)round(13.12 + (0.6215 * temp) - (11.37 * pow(wind, 0.16)) + (0.3965 * (0.16 * temp) * pow(wind, 0.16)));
}