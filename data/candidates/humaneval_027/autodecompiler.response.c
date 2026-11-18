void func0(char *str,char *str1)
{
 int i;
 int len = strlen(str);
 for(i=0;i<len;i++)
 {
  char ch = str[i];
  if(ch >= 'a' && ch <= 'z')
  {
   ch = ch - 32;
  }
  else if(ch >= 'A' && ch <= 'Z')
  {
   ch = ch + 32;
  }
  str1[i] = ch;
 }
 str1[len] = '\0';
}