char *__cdecl func0(const char *text)
{
  char v1; // dl
  int v2; // ecx
  char v3; // dl
  int v4; // ecx
  int j; // [rsp+8h] [rbp-28h]
  int i; // [rsp+Ch] [rbp-24h]
  char *result; // [rsp+10h] [rbp-20h]
  unsigned __int64 length; // [rsp+20h] [rbp-10h]

  length = strlen(text);
  result = (char *)malloc(2 * length);
  j = 0;
  for ( i = 0; i < length; ++i )
  {
    if ( i > 0
      && ((*__ctype_b_loc())[text[i]] & 0x100) != 0
      && (((*__ctype_b_loc())[text[i - 1]] & 0x200) != 0 || ((*__ctype_b_loc())[text[i - 1]] & 0x800) != 0)
      || i > 0
      && ((*__ctype_b_loc())[text[i]] & 0x100) != 0
      && ((*__ctype_b_loc())[text[i - 1]] & 0x100) != 0
      && ((*__ctype_b_loc())[text[i + 1]] & 0x200) != 0 )
    {
      result[j] = 95;
      v1 = tolower(text[i]);
      v2 = j + 1;
      j += 2;
      result[v2] = v1;
    }
    else
    {
      v3 = tolower(text[i]);
      v4 = j++;
      result[v4] = v3;
    }
  }
  result[j] = 0;
  return result;
}