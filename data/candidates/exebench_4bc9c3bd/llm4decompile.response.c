int escape(char *fmt,int percent,size_t *len)
{
  char *save=fmt,*tmp=fmt;
  int value;
  char ch;
  int count;
  while((ch=*fmt++)!=0)
    {
      if (ch!='\\')
 *tmp++=ch;
      else
 {
   switch(ch=*fmt++)
     {
    case 0:
      *tmp++='\\';
      *tmp=0;
      *len=tmp-save;
      return 0;
    case '\\':
    case '\'':
      *tmp++=ch;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
      value=0;
      count=(percent?3:4);
      if (!percent && ch=='0')
 count--;
      while(count-- && *fmt>='0' && *fmt<='7')
 value=value*8+*fmt++-'0';
      fmt--;
      if (percent && value=='%')
 {
   *tmp++='%';
   *tmp++='%';
 }
      else
 *tmp++=value;
      break;
    case 'a':
      *tmp++='\a';
      break;
    case 'b':
      *tmp++='\b';
      break;
    case 'c':
      if (percent)
 *tmp++=ch;
      else
 {
   *tmp=0;
   *len=tmp-save;
   return 1;
 }
      break;
    case 'f':
      *tmp++='\f';
      break;
    case 'n':
      *tmp++='\n';
      break;
    case 'r':
      *tmp++='\r';
      break;
    case 't':
      *tmp++='\t';
      break;
    case 'v':
      *tmp++='\v';
      break;
     }
 }
    }
  *tmp=0;
  *len=tmp-save;
  return 0;
}