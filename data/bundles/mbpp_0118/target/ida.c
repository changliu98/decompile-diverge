char **__cdecl func0(const char *string)
{
  char *v1; // rax
  int v2; // ecx
  const char *token; // [rsp+0h] [rbp-40h]
  int index; // [rsp+Ch] [rbp-34h]
  char *str; // [rsp+10h] [rbp-30h]
  char **list; // [rsp+18h] [rbp-28h]
  const char *ptr; // [rsp+20h] [rbp-20h]
  int count; // [rsp+2Ch] [rbp-14h]

  count = 1;
  for ( ptr = string; *ptr; ++ptr )
  {
    if ( *ptr == 32 )
      ++count;
  }
  list = (char **)malloc(8LL * (count + 1));
  if ( !list )
    return 0LL;
  str = strdup(string);
  if ( str )
  {
    index = 0;
    for ( token = strtok(str, " "); token; token = strtok(0LL, " ") )
    {
      v1 = strdup(token);
      v2 = index++;
      list[v2] = v1;
    }
    list[index] = 0LL;
    free(str);
    return list;
  }
  else
  {
    free(list);
    return 0LL;
  }
}