char bppm_symbol(float *x)
{
  char c;

  if (x[0] > 0.5)
    c = '.';
  else if (x[1] > 0.5)
    c = '(';
  else if (x[2] > 0.5)
    c = ')';
  else if (x[0] > x[1] + x[2])
    c = ',';
  else if (x[0] < x[1] + x[2])
    c = ':';
  else if (x[1] / (x[1] + x[2]) > 0.5)
    c = '{';
  else if (x[2] / (x[1] + x[2]) > 0.5)
    c = '}';
  else
    c = '|';

  return c;
}