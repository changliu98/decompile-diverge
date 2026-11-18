char *smtp_stpcpy(char *dest, char *src)
{
 long i;

 i = 0;
 while ((int)src[i] != 0)
 {
  dest[i] = src[i];
  i++;
 }
 return (&dest[i - 1]);
}