char *func0(char **test, int size)
{
 char *delim = "-";
 int i;
 test = test;
 size = size;
 strcpy(res,"");
 for(i=0; i < size; i++)
 {
  strcat(res,test[i]);
  if(i < size - 1)
   strcat(res,delim);
 }
 return res;
}