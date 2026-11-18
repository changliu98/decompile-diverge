char *func0(char *str)
{
 size_t i;
 int j = 0;
 for(i = 0; ; i++) {
  if(i >= strlen(str)) {
   str[j] = '\0';
   break;
  }
  if(!((*___ctype_b_loc ())[(int) ((str[i]))] & (unsigned short int) 8192))
   str[j++] = str[i];
 }
 return str;
}