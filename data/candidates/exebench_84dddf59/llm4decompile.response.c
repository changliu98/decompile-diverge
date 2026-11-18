void ck_decrypt(char *s)
{
  char *p;

  for (p = s; *p; p++) {
    if (*p != 'p' && *p != '\\' && *p != 'S')
      *p ^= 0xf;
  }
}