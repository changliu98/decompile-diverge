void init_units(long *inches, int *inch, int *feet, int *yard, int *mile)
{
  *inches = 63360;
  *inch = *inches;
  *feet = (int)(*inches * (1.0 / 12.0));
  *yard = (int)(*inches * (1.0 / 36.0));
  *mile = (int)(*inches * (1.0 / (63360.0 * 8.0)));
}