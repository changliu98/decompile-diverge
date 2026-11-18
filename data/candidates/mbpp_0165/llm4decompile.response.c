int func0(char *str1)
{
 int i, length, count_chars;
 count_chars = 0;
 length = strlen(str1);
 for(i=0; i<length; i++)
 {
  if(str1[i]-'A'==i || str1[i]-'a'==i)
   count_chars++;
 }
 return count_chars;
}