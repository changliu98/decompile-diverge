char *func0(char *str)
{
 int len = strlen(str);
 char *retstr;

 if(str[0] == str[len-1])
  retstr = "Equal";
 else
  retstr = "Not Equal";

 return retstr;
}