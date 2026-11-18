int
fatfs_get_sfn_display_name(char *s, char *t)
{
 int i;
 char c;

 i = 0;
 for (;;) {
  if (((*t == '\0') || (i >= 12)))
   break;
  c = *t++;
  if (c == ' ')
   continue;
  if ((c >= 'A') && (c <= 'Z'))
   c += 'a' - 'A';
  *s++ = c;
  i++;
 }
 *s = '\0';
 return(1);
}