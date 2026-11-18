void set_char(void *from, void *to, unsigned int length)
{
  char *f = (char *) from;
  char *t = (char *) to;
  while (length--)
    *t++ = *f++;
}