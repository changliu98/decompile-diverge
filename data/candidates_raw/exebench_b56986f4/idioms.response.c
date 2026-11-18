void init_ip(int n, int ip[])
{
  int i; int j; int k; int l;
  ip[2] = 0;
  ip[3] = 16;
  for (i = 2, k = 2; n > 32; i = i * 2, k = k * 2, n = n / 4)
    for (j = i; j < i * 2; j++)
      {
 l = ip[j] * 4;
 ip[j + i] = l;
 ip[j + i * 2] = l + i * 16;
      }
}