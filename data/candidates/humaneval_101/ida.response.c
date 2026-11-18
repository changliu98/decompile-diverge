char **__cdecl func0(const char *s, int *count)
{
  size_t v2; // rax
  char *v3; // rax
  int v4; // ecx
  int v5; // ecx
  char *v6; // rdx
  int v7; // ecx
  int i; // [rsp+Ch] [rbp-34h]
  int current_length; // [rsp+10h] [rbp-30h]
  int word_count; // [rsp+14h] [rbp-2Ch]
  char *current; // [rsp+18h] [rbp-28h]
  char **out; // [rsp+20h] [rbp-20h]
  int capacity; // [rsp+2Ch] [rbp-14h]

  capacity = 10;
  out = (char **)malloc(0x50uLL);
  v2 = strlen(s);
  current = (char *)malloc(v2 + 1);
  word_count = 0;
  current_length = 0;
  for ( i = 0; s[i]; ++i )
  {
    if ( s[i] == 32 || s[i] == 44 )
    {
      if ( current_length > 0 )
      {
        current[current_length] = 0;
        v3 = strdup(current);
        v4 = word_count++;
        out[v4] = v3;
        current_length = 0;
        if ( word_count >= capacity )
        {
          capacity *= 2;
          out = (char **)realloc(out, 8LL * capacity);
        }
      }
    }
    else
    {
      v5 = current_length++;
      current[v5] = s[i];
    }
  }
  if ( current_length > 0 )
  {
    current[current_length] = 0;
    v6 = strdup(current);
    v7 = word_count++;
    out[v7] = v6;
  }
  free(current);
  *count = word_count;
  return out;
}