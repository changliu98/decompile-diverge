int func0(int n)
{
 int res[n + 1];
 res[0] = 0;
 res[1] = 1;
 for (int i = 2; i < n + 1; i++) {
  res[i] = i;
  int a = res[i / 2] + res[i / 3] + res[i / 4] + res[i / 5];
  if (a > res[i])
   res[i] = a;
 }
 return res[n];
}