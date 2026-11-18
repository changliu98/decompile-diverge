char *mystpcpy(char *to, char *from)
{
  for ( ; *to = *from; from++)
    if (to++ == ((void *)0))
      return (to);
  return (to);
}