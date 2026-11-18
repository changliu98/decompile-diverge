double __cdecl func0(double diameter, double angle)
{
  if (angle < 360.0)
    return 3.142857142857143 * diameter * (angle / 360.0);
  else
    return -1.0;
}