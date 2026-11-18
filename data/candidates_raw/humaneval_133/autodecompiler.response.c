int vceilmulsum(float *v, int n)
{
 int i, s = 0;
 for(i = 0; i < n; i++)
  s += ceil(v[i]) * ceil(v[i]);
 return s;
}