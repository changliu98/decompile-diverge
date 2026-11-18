char *__cdecl ft_strcpy(char *s1, const char *s2)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *s1a; // [rsp+10h] [rbp-8h]

  s1a = s1;
  while ( *s2 )
  {
    v2 = s2++;
    v3 = *v2;
    v4 = s1a++;
    *v4 = v3;
  }
  *s1a = 0;
  return s1;
}