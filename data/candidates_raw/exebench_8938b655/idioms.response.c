int itoa(int i, char s[])
{
  int j = i;
  int k = -1;
  int l = 0;
  int digit = 0;
  char temp = ' ';
  if ( i < 0 )
  {
    k = 0;
    j = -i;
    l = 1;
    s[k] = '-';
  }
  else
  {
    k = -1;
    l = 0;
  }
  do
  {
    digit = j % 10;
    j /= 10;
    s[++k] = digit + '0';
  } while ( j != 0 );
  s[++k] = '\0';
  l = k + 1;
  while ( l < k )
  {
    temp = s[l];
    s[l] = s[k];
    s[k] = temp;
    l++;
    k--;
  }
  return l;
}