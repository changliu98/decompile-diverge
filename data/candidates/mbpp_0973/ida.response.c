char *__cdecl func0(char *s, int d)
{
  int i; // [rsp+14h] [rbp-1Ch]
  char *tmp; // [rsp+18h] [rbp-18h]
  int len; // [rsp+20h] [rbp-10h]

  len = strlen(s);
  tmp = (char *)malloc(len + 1);
  for ( i = 0; i < len; ++i )
    tmp[i] = s[(d + i) % len];
  tmp[len] = 0;
  return tmp;
}