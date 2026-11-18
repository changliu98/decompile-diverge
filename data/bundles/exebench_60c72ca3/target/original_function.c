void string_rip(char str[], const char *ripper)
{
 char *t_ptr = str;

 while (*str) {
  const char *ripper_idx = ripper;
  int skip_this = 0;

  while (*ripper_idx) {
   if (*str == *ripper_idx) {
    skip_this = 1;
    break;
   }
   ripper_idx++;
  }

  if (skip_this)
   str++;
  else
   *t_ptr++ = *str++;
 }

 *t_ptr = '\0';
}