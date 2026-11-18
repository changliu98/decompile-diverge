char * blank_to_colon(char *str)
{
 int i;

 for(i=0; str[i] != '\0'; i++)
 {
  if(str[i]==' ' || str[i]==',' || str[i]=='.')
   str[i]=':';
 }
 return str;
}