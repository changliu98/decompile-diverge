void rev(char s[])
{
 int i, j;
 char c;
 int len = 0;

 while(s[len] != '\0')
 {
  len++;
 }

 for(i = 0; i < len/2; i++)
 {
  c = s[i];
  s[i] = s[len-i-1];
  s[len-i-1] = c;
 }
}