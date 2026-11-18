// Calculates a value based on radius (r) and height (h)
// using a constant multiplier DAT_00102008
// Formula: result = DAT_00102008 * r^2 * h
double func0(double radius, double height)
{
  return MULTIPLIER * radius * radius * height;
}