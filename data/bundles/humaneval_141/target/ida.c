const char *__cdecl func0(const char *file_name)
{
  int i; // [rsp+4h] [rbp-2Ch]
  const char *last; // [rsp+8h] [rbp-28h]
  char w; // [rsp+13h] [rbp-1Dh]
  int length; // [rsp+14h] [rbp-1Ch]
  int num_dot; // [rsp+18h] [rbp-18h]
  int num_digit; // [rsp+1Ch] [rbp-14h]

  num_digit = 0;
  num_dot = 0;
  length = strlen(file_name);
  if ( length < 5 )
    return (const char *)&unk_2004;
  w = *file_name;
  if ( *file_name < 65 || w > 90 && w < 97 || w > 122 )
    return (const char *)&unk_2004;
  last = &file_name[length - 4];
  if ( strcmp(last, ".txt") && strcmp(last, ".exe") && strcmp(last, ".dll") )
    return (const char *)&unk_2004;
  for ( i = 0; i < length; ++i )
  {
    if ( file_name[i] >= 48 && file_name[i] <= 57 )
      ++num_digit;
    if ( file_name[i] == 46 )
      ++num_dot;
  }
  if ( num_digit <= 3 && num_dot == 1 )
    return "Yes";
  else
    return (const char *)&unk_2004;
}