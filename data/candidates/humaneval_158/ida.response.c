char *__cdecl func0(char **words, int count)
{
  int len; // [rsp+4h] [rbp-12Ch]
  int j; // [rsp+8h] [rbp-128h]
  int unique_count; // [rsp+Ch] [rbp-124h]
  char unique[256]; // [rsp+10h] [rbp-120h] BYREF
  int i; // [rsp+110h] [rbp-20h]
  int maxu; // [rsp+114h] [rbp-1Ch]
  char *max; // [rsp+118h] [rbp-18h]
  int counta; // [rsp+124h] [rbp-Ch]
  char **wordsa; // [rsp+128h] [rbp-8h]

  wordsa = words;
  counta = count;
  max = (char *)"";
  maxu = 0;
  for ( i = 0; i < counta; ++i )
  {
    memset(unique, 0, sizeof(unique));
    unique_count = 0;
    for ( j = 0; wordsa[i][j]; ++j )
    {
      if ( !strchr(unique, wordsa[i][j]) )
      {
        len = strlen(unique);
        unique[len] = wordsa[i][j];
        unique[len + 1] = 0;
        ++unique_count;
      }
    }
    if ( unique_count > maxu || unique_count == maxu && strcmp(wordsa[i], max) < 0 )
    {
      max = wordsa[i];
      maxu = unique_count;
    }
  }
  return max;
}