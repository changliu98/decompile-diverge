int itos(int n, char s[])
{
 int i, j, sign;
 int len;

 if(n < 0)
 {
  i = 0;
  n = -n;
  j = 1;
  s[0] = '-';
 }
 else
 {
  i = -1;
  j = 0;
 }

 do
 {
  s[++i] = n % 10 + '0';
 }while(n /= 10);

 s[++i] = '\0';

 len = i;

 while(j < i)
 {
  char temp;
  temp = s[j];
  s[j] = s[i];
  s[i] = temp;
  j++;
  i--;
 }

 return len;
}