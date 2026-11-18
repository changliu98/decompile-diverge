char *__cdecl func0(const char *string)
{
  int v1; // eax
  int i_1; // [rsp+4h] [rbp-36Ch]
  char *result; // [rsp+8h] [rbp-368h]
  int i_0; // [rsp+10h] [rbp-360h]
  int total_length; // [rsp+14h] [rbp-35Ch]
  int i; // [rsp+18h] [rbp-358h]
  int found; // [rsp+1Ch] [rbp-354h]
  const char *token; // [rsp+20h] [rbp-350h]
  int unique_count; // [rsp+2Ch] [rbp-344h]
  char *unique[100]; // [rsp+30h] [rbp-340h]
  char *str; // [rsp+358h] [rbp-18h]
  const char *stringa; // [rsp+360h] [rbp-10h]

  stringa = string;
  str = strdup(string);
  if ( !str )
    return 0LL;
  unique_count = 0;
  for ( token = strtok(str, " "); token; token = strtok(0LL, " ") )
  {
    found = 0;
    for ( i = 0; i < unique_count; ++i )
    {
      if ( !strcmp(token, unique[i]) )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
    {
      v1 = unique_count++;
      unique[v1] = (char *)token;
    }
  }
  total_length = 0;
  for ( i_0 = 0; i_0 < unique_count; ++i_0 )
    total_length += strlen(unique[i_0]) + 1;
  result = (char *)malloc(total_length);
  if ( result )
  {
    *result = 0;
    for ( i_1 = 0; i_1 < unique_count; ++i_1 )
    {
      strcat(result, unique[i_1]);
      if ( i_1 < unique_count - 1 )
        strcat(result, " ");
    }
    free(str);
    return result;
  }
  else
  {
    free(str);
    return 0LL;
  }
}