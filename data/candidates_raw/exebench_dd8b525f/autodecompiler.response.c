void reverse(char s[])
{
 int i,j;
 char temp;

 j = 0;
 while(s[j] != '\0')
 {
  j++;
 }
 j--;
 if(s[j] == '\n')
  j--;

 for(i=0; i<j; i++)
 {
  temp = s[i];
  s[i] = s[j];
  s[j] = temp;
  j--;
 }
}