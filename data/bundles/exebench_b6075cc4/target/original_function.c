void
break_atr(char str[], char c)
{
 char *const p = strrchr(str, c);
 if(p != NULL)
 {
  *p = '\0';
 }
}