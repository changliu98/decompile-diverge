char* func0(char* str)
{
 int i;
 int j = 0;
 for(i=0;;i++)
 {
  if(str[i] == '\0')
   break;
  if(!((*((short unsigned int *)__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short int) 512)))
  {
   func0_result[j++] = str[i];
  }
 }
 func0_result[j] = '\0';
 return func0_result;
}