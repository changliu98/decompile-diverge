int __cdecl func0(char **strings, int count, const char *prefix, char ***out)
{
  int v4; // ecx
  int i; // [rsp+4h] [rbp-2Ch]
  int out_count; // [rsp+8h] [rbp-28h]
  int prefix_length; // [rsp+Ch] [rbp-24h]

  prefix_length = strlen(prefix);
  *out = (char **)malloc(8LL * count);
  out_count = 0;
  for ( i = 0; i < count; ++i )
  {
    if ( !strncmp(strings[i], prefix, prefix_length) )
    {
      v4 = out_count++;
      (*out)[v4] = strings[i];
    }
  }
  return out_count;
}