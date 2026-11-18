char *__cdecl strcpy(char *s1, const char *s2)
{
  int v2; // ecx
  int i; // [rsp+0h] [rbp-14h]

  i = 0;
  do
  {
    s1[i] = s2[i];
    v2 = i++;
  }
  while ( s2[v2] );
  return s1;
}