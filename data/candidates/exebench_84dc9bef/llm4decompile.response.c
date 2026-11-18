void trim(char *str)
{
 int i;
 for(i=0;str[i]!='\0';i++);
 str[i-1]='\0';
}