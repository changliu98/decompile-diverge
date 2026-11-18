char *jstrescapecpy(char *buffer, char *msaccess_dbname)
{
 int i,j;
 char *ret;

 i=0;
 j=0;
 if (msaccess_dbname==NULL) {
  buffer[0]=0;
  ret=buffer;
 } else {
  while (msaccess_dbname[i]!=0) {
   switch (msaccess_dbname[i]) {
   case '\'':
    buffer[j++]='\\';
    buffer[j++]=msaccess_dbname[i++];
    break;
   case '\\':
    buffer[j++]='\\';
    buffer[j++]=msaccess_dbname[i++];
    break;
   case '%':
    buffer[j]='_';
    i++;
    break;
   default:
    buffer[j++]=msaccess_dbname[i++];
   }
  }
  buffer[j++]=0;
  ret=buffer;
 }
 return ret;
}