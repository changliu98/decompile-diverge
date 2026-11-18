char **__cdecl func0(const char *text)
{
  size_t v1; // rax
  char *v2; // rdx
  int v3; // ecx
  bool v5; // [rsp+6h] [rbp-3Ah]
  bool v6; // [rsp+7h] [rbp-39h]
  char *end; // [rsp+10h] [rbp-30h]
  const char *token; // [rsp+18h] [rbp-28h]
  char *copy; // [rsp+20h] [rbp-20h]
  int count; // [rsp+2Ch] [rbp-14h]
  char **result; // [rsp+30h] [rbp-10h]

  v1 = strlen(text);
  result = (char **)malloc(8 * ((v1 >> 1) + 1));
  count = 0;
  copy = strdup(text);
  for ( token = strtok(copy, " "); token; token = strtok(0LL, " ") )
  {
    for ( end = (char *)&token[strlen(token) - 1]; ; --end )
    {
      v6 = 0;
      if ( end > token )
      {
        v5 = 1;
        if ( *end != 46 )
        {
          v5 = 1;
          if ( *end != 44 )
          {
            v5 = 1;
            if ( *end != 33 )
            {
              v5 = 1;
              if ( *end != 63 )
              {
                v5 = 1;
                if ( *end != 59 )
                  v5 = *end == 58;
              }
            }
          }
        }
        v6 = v5;
      }
      if ( !v6 )
        break;
      *end = 0;
    }
    if ( strlen(token) >= 4 )
    {
      v2 = strdup(token);
      v3 = count++;
      result[v3] = v2;
    }
  }
  result[count] = 0LL;
  free(copy);
  return result;
}