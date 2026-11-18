void intToString(int n, char s[])
{
 int i, j, k;
 if(n == 0)
 {
  s[0] = '0';
  s[1] = '\0';
  return;
 }
 for(i = 0, j = n; j != 0; ++i)
  j /= 10;
 s[i] = '\0';
 --i;
 for(k = n; i >= 0; --i, k /= 10)
  s[i] = k % 10 + '0';
}