char **__cdecl func0(char **strings, int size, const char *substring, int *out_size)
{
  int i; // [rsp+0h] [rbp-30h]
  int count; // [rsp+4h] [rbp-2Ch]
  char **out; // [rsp+8h] [rbp-28h]

  out = 0LL;
  count = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( strstr(strings[i], substring) )
    {
      out = (char **)realloc(out, 8LL * (count + 1));
      out[count++] = strings[i];
    }
  }
  *out_size = count;
  return out;
}