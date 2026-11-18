char *func0(char str[])
{
 int len;
 char *ptr;

 len = strlen(str);

 if(str[0] == str[len-1])
 {
  ptr = "Equal";
 }
 else
 {
  ptr = "Not Equal";
 }

 return ptr;
}