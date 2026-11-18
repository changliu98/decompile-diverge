char **__cdecl func0(const char *s, int n, int *returnSize)
{
  size_t v3; // rax
  int i; // [rsp+4h] [rbp-4Ch]
  char *current; // [rsp+8h] [rbp-48h]
  unsigned __int64 length; // [rsp+10h] [rbp-40h]
  int begin; // [rsp+1Ch] [rbp-34h]
  int word_count; // [rsp+20h] [rbp-30h]
  int numc; // [rsp+24h] [rbp-2Ch]
  char **out; // [rsp+28h] [rbp-28h]

  out = 0LL;
  numc = 0;
  word_count = 0;
  begin = 0;
  length = strlen(s);
  current = (char *)malloc(length + 1);
  for ( i = 0; i <= length; ++i )
  {
    if ( ((*__ctype_b_loc())[s[i]] & 0x2000) == 0 && s[i] )
    {
      current[i - begin] = s[i];
      if ( !strchr("aeiouAEIOU", s[i]) && ((*__ctype_b_loc())[(unsigned __int8)s[i]] & 0x400) != 0 )
        ++numc;
    }
    else
    {
      if ( numc == n )
      {
        current[i - begin] = 0;
        out = (char **)realloc(out, 8LL * (word_count + 1));
        v3 = strlen(current);
        out[word_count] = (char *)malloc(v3 + 1);
        strcpy(out[word_count++], current);
      }
      begin = i + 1;
      numc = 0;
    }
  }
  free(current);
  *returnSize = word_count;
  return out;
}