char *__cdecl object_desc_chr(char *t, char c)
{
  *t = c;
  t[1] = 0;
  return t + 1;
}