sds *__cdecl sdssplitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count)
{
  int i; // [rsp+4h] [rbp-5Ch]
  sds *newtokens; // [rsp+8h] [rbp-58h]
  sds *tokens; // [rsp+10h] [rbp-50h]
  long j; // [rsp+18h] [rbp-48h]
  long start; // [rsp+20h] [rbp-40h]
  int slots; // [rsp+28h] [rbp-38h]
  int elements; // [rsp+2Ch] [rbp-34h]

  elements = 0;
  slots = 5;
  start = 0LL;
  if ( seplen >= 1 && len > 0 )
  {
    tokens = (sds *)malloc(0x28uLL);
    if ( tokens )
    {
      for ( j = 0LL; j < len - (seplen - 1); ++j )
      {
        if ( slots < elements + 2 )
        {
          slots *= 2;
          newtokens = (sds *)realloc(tokens, 8LL * slots);
          if ( !newtokens )
            goto cleanup;
          tokens = newtokens;
        }
        if ( seplen == 1 && s[j] == *sep || !memcmp(&s[j], sep, seplen) )
        {
          tokens[elements] = sdsnewlen(&s[start], j - start);
          if ( !tokens[elements] )
            goto cleanup;
          ++elements;
          start = seplen + j;
          j = start - 1;
        }
      }
      tokens[elements] = sdsnewlen(&s[start], len - start);
      if ( tokens[elements] )
      {
        *count = elements + 1;
        return tokens;
      }
cleanup:
      for ( i = 0; i < elements; ++i )
        sdsfree(tokens[i]);
      free(tokens);
      *count = 0;
      return 0LL;
    }
    else
    {
      return 0LL;
    }
  }
  else
  {
    *count = 0;
    return 0LL;
  }
}