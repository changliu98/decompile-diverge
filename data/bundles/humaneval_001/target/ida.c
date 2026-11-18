char **__cdecl func0(const char *paren_string, int *group_count)
{
  int v2; // ecx
  int v3; // ecx
  char chr; // [rsp+7h] [rbp-39h]
  int i; // [rsp+8h] [rbp-38h]
  int buffer_index; // [rsp+Ch] [rbp-34h]
  char *buffer; // [rsp+10h] [rbp-30h]
  char **groups; // [rsp+18h] [rbp-28h]
  int capacity; // [rsp+24h] [rbp-1Ch]
  int level; // [rsp+28h] [rbp-18h]
  int length; // [rsp+2Ch] [rbp-14h]

  length = strlen(paren_string);
  level = 0;
  capacity = 10;
  groups = (char **)malloc(0x50uLL);
  buffer = (char *)malloc(length + 1);
  buffer_index = 0;
  *group_count = 0;
  for ( i = 0; i < length; ++i )
  {
    chr = paren_string[i];
    if ( chr == 40 )
    {
      ++level;
      v2 = buffer_index++;
      buffer[v2] = chr;
    }
    else if ( chr == 41 )
    {
      --level;
      v3 = buffer_index++;
      buffer[v3] = chr;
      if ( !level )
      {
        buffer[buffer_index] = 0;
        groups[(*group_count)++] = strdup(buffer);
        if ( *group_count >= capacity )
        {
          capacity *= 2;
          groups = (char **)realloc(groups, 8LL * capacity);
        }
        buffer_index = 0;
      }
    }
  }
  free(buffer);
  return groups;
}