char *func0(char *str)
{
 int i;
 for(i = 0;; i++)
 {
  if(str[i] == '\0')
   break;
  func0_result[i] = toupper((unsigned char)str[i]);
 }
 func0_result[i] = '\0';
 return func0_result;
}