char **__cdecl func0(const char *text, int *count)
{
  int i; // [rsp+8h] [rbp-28h]
  int word_start; // [rsp+Ch] [rbp-24h]
  char **result; // [rsp+10h] [rbp-20h]
  int n; // [rsp+1Ch] [rbp-14h]

  n = strlen(text);
  result = (char **)malloc(8LL * n);
  *count = 0;
  word_start = 0;
  for ( i = 1; i <= n; ++i )
  {
    if ( i == n || ((*__ctype_b_loc())[text[i]] & 0x100) != 0 && ((*__ctype_b_loc())[text[i - 1]] & 0x100) == 0 )
    {
      result[*count] = (char *)malloc(i - word_start + 1);
      strncpy(result[*count], &text[word_start], i - word_start);
      result[(*count)++][i - word_start] = 0;
      word_start = i;
    }
  }
  return result;
}