void
break_at(char str[], char c)
{
 char *const p = strchr(str, c);
 if(p != NULL)
 {
  *p = '\0';
 }
}