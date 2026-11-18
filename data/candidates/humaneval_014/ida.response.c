char **__cdecl func0(const char *str, int *count)
{
  size_t v2; // rax
  size_t current_len; // [rsp+8h] [rbp-38h]
  int i; // [rsp+14h] [rbp-2Ch]
  char *current; // [rsp+18h] [rbp-28h]
  char **out; // [rsp+20h] [rbp-20h]
  int len; // [rsp+2Ch] [rbp-14h]

  len = strlen(str);
  out = (char **)malloc(8LL * len);
  current = (char *)malloc(len + 1);
  *current = 0;
  for ( i = 0; i < len; ++i )
  {
    current_len = strlen(current);
    current = (char *)realloc(current, current_len + 2);
    current[current_len] = str[i];
    current[current_len + 1] = 0;
    v2 = strlen(current);
    out[i] = (char *)malloc(v2 + 1);
    strcpy(out[i], current);
  }
  free(current);
  *count = len;
  return out;
}