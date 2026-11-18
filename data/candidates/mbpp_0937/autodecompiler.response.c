int func0(char *str)
{
 int freq[256];
 memset(freq, 0, sizeof(freq));
 int max = 0;
 char c = 0;
 int len = strlen(str);
 int i = 0;

 while(i < len)
 {
  freq[str[i]]++;
  if(freq[str[i]] > max)
  {
   max = freq[str[i]];
   c = str[i];
  }
  i++;
 }

 return c;
}