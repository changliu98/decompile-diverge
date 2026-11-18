char *__cdecl object_desc_chr(char *t, char c)
{
  t[0] = c;
  t[1] = '\0';
  return t + 1;
}