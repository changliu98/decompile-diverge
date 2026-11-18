int str2int(char *str)
{
  double d = atof(str);
  if (d < 0.0)
    return (int)(ceil(d - 0.5));
  else
    return (int)(floor(d + 0.5));
}