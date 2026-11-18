void ck_encrypt(char *s)
{
  char *cp;

  for (cp = s; *cp; cp++)
    if (*cp != 'p' && *cp != '\\' && *cp != 'S')
      *cp = *cp ^ 15;
}