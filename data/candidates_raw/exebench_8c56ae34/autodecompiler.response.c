void reverse(char s[])
{
 int i,j;
 char temp;

 i = 0;
 j = 0;

 while(s[j] != '\0')
 {
  j++;
 }
 j--;
 if(s[j] == '\n')
  j--;

 while(i < j)
 {
  temp = s[i];
  s[i] = s[j];
  s[j] = temp;
  j--;
  i++;
 }
}