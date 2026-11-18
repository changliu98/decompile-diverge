void
scsi_sanitize_inquiry_string(char *s, int len)
{
 int c = 0;
 for (;;) {
  if (len <= 0)
   return;

  if (*s == '\0')
   c = 1;

  if (c || *s < 32 || *s > 126)
   *s = ' ';

  len--;
  s++;
 }
}