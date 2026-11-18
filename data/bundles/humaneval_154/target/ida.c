bool __cdecl func0(const char *a, const char *b)
{
  int i; // [rsp+4h] [rbp-2Ch]
  char *temp; // [rsp+8h] [rbp-28h]
  int len_b; // [rsp+10h] [rbp-20h]

  strlen(a);
  len_b = strlen(b);
  temp = (char *)malloc(2 * len_b + 1);
  for ( i = 0; i < len_b; ++i )
  {
    strncpy(temp, &b[i], len_b - i);
    strncpy(&temp[len_b - i], b, i);
    temp[len_b] = 0;
    if ( strstr(a, temp) )
    {
      free(temp);
      return 1;
    }
  }
  free(temp);
  return 0;
}