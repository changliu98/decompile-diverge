int func0(int a, int b)
{
  int c;
  int d;
  int e;
  int f;
  int g;
  int h;
  int i;
  int j;
  int k;
  int l;
  int m;
  int n;
  int o;
  int p;
  int q;
  int r;
  int s;
  int t;
  int u;
  int v;
  int w;
  int x;
  int y;
  int z;

  if (a < b)
    c = a;
  else
    c = b;

  if (a > b)
    d = a;
  else
    d = b;

  if (c == 0)
    e = d;
  else if (c == 1)
    e = 1;
  else
    e = func0(c, d % c);

  return e;
}