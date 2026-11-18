int func0(float a, float b, float c)
{
  int result;
  if (fabs(-a*a+b*b+c*c) < 0.0001)
    result = 1;
  else if (fabs(-b*b+a*a+c*c) < 0.0001)
    result = 1;
  else if (fabs(-c*c+a*a+b*b) < 0.0001)
    result = 1;
  else
    result = 0;
  return result;
}