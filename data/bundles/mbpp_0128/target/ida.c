char **__cdecl func0(int n, char *str, int *count)
{
  int v3; // eax
  const char *token; // [rsp+8h] [rbp-28h]
  int index; // [rsp+14h] [rbp-1Ch]

  index = 0;
  for ( token = strtok(str, " "); token; token = strtok(0LL, " ") )
  {
    if ( strlen(token) > n )
    {
      v3 = index++;
      func0_word_len[v3] = token;
    }
  }
  *count = index;
  return (char **)func0_word_len;
}