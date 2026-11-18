char **__cdecl func0(const char *text, int *count)
{
  int word_length; // [rsp+0h] [rbp-30h]
  int i; // [rsp+4h] [rbp-2Ch]
  int start; // [rsp+8h] [rbp-28h]
  int current_word; // [rsp+Ch] [rbp-24h]
  char **result; // [rsp+10h] [rbp-20h]
  int len; // [rsp+1Ch] [rbp-14h]

  len = strlen(text);
  result = (char **)malloc(8LL * len);
  if ( !result )
  {
    perror("Failed to allocate memory");
    exit(1);
  }
  current_word = 0;
  start = 0;
  for ( i = 1; i <= len; ++i )
  {
    if ( ((*__ctype_b_loc())[text[i]] & 0x100) != 0 || !text[i] )
    {
      word_length = i - start;
      result[current_word] = (char *)malloc(i - start + 1);
      if ( !result[current_word] )
      {
        perror("Failed to allocate memory");
        exit(1);
      }
      memcpy(result[current_word], &text[start], word_length);
      result[current_word][word_length] = 0;
      start = i;
      ++current_word;
    }
  }
  *count = current_word;
  return result;
}