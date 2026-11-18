void itoa(int n, char s[])
{
  int i = 10;
  for (i = 10; i > 0; i--) {
    s[i] = n % 10 + '0';
    n /= 10;
  }
  s[10] = '\0';
}