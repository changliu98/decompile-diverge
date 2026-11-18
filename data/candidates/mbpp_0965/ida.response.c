char *__cdecl func0(const char *text)
{
  int v1; // eax
  char v2; // dl
  int v3; // eax
  int v4; // eax
  int j; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  i = 0;
  j = 0;
  while ( text[i] )
  {
    if ( ((*__ctype_b_loc())[text[i]] & 0x100) != 0 )
    {
      if ( i && (((*__ctype_b_loc())[text[i - 1]] & 0x200) != 0 || ((*__ctype_b_loc())[text[i - 1]] & 0x800) != 0) )
      {
        v1 = j++;
        func0_buffer[v1] = 95;
      }
      v2 = tolower(text[i]);
      v3 = j++;
      func0_buffer[v3] = v2;
    }
    else
    {
      v4 = j++;
      func0_buffer[v4] = text[i];
    }
    ++i;
  }
  func0_buffer[j] = 0;
  return func0_buffer;
}