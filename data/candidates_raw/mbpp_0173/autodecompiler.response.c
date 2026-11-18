char *trim(char *str)
{
 int i = 0;
 int j = 0;
 char tmp[strlen(str) + 1];

 while (1) {
  if (str[i] == '\0')
   break;

  if (*(___ctype_b_loc () + 1)[(int) ((str[i]))] & (unsigned short int) 8)
   tmp[j++] = str[i];

  i++;
 }

 tmp[j] = '\0';
 strcpy(str, tmp);

 return str;
}