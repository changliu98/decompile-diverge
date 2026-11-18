char *gen_c_name(char *_name,char *buf)
{
 int i,capitalize=0;
 int j=0;

 for(i=0;;i++)
 {
  if (_name[i] == '\0')
   break;

  if (_name[i] == '_')
  {
   capitalize = 1;
   continue;
  }

  if (capitalize)
  {
   buf[j++] = toupper(_name[i]);
   capitalize = 0;
  }
  else
   buf[j++] = _name[i];
 }

 buf[j] = '\0';
 return buf;
}