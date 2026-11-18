unsigned short calc_speed(unsigned short *v, int n, unsigned short def)
{
  int i;
  unsigned short m=0;

  for (i=0; i<n; i++)
    if (m<v[i]) m=v[i];
  if (m==0) m=def;
  return m;
}