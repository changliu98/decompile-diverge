int f(int x)
{
  _Bool c;

  if(x%4==2) c=1;
  else c=0;

  return c&1;
}