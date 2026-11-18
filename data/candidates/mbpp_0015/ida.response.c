char **__cdecl func0(const char *text, int *count)
{
  char v3; // [rsp+7h] [rbp-39h]
  char *substr; // [rsp+8h] [rbp-38h]
  int start; // [rsp+1Ch] [rbp-24h]
  int i; // [rsp+20h] [rbp-20h]
  _BYTE len[12]; // [rsp+24h] [rbp-1Ch]

  *(_DWORD *)&len[8] = 0;
  *count = 0;
  *(_QWORD *)len = (unsigned int)strlen(text);
  i = 0;
  while ( i < *(int *)len )
  {
    if ( ((*__ctype_b_loc())[(unsigned __int8)text[i]] & 0x200) != 0 )
    {
      start = i++;
      while ( 1 )
      {
        v3 = 0;
        if ( i < *(int *)len )
          v3 = ~(((*__ctype_b_loc())[(unsigned __int8)text[i]] & 0x200) != 0);
        if ( (v3 & 1) == 0 )
          break;
        ++i;
      }
      substr = (char *)malloc(i - start + 1);
      strncpy(substr, &text[start], i - start);
      substr[i - start] = 0;
      *(_QWORD *)&len[4] = realloc(*(void **)&len[4], 8LL * (*count + 1));
      *(_QWORD *)(*(_QWORD *)&len[4] + 8LL * (*count)++) = substr;
    }
    else
    {
      ++i;
    }
  }
  return *(char ***)&len[4];
}