const char *__cdecl func0(const char *string)
{
  int j; // [rsp+8h] [rbp-58h]
  int i; // [rsp+Ch] [rbp-54h]
  int found[10]; // [rsp+10h] [rbp-50h] BYREF
  int count; // [rsp+40h] [rbp-20h]
  char vowels[11]; // [rsp+45h] [rbp-1Bh] BYREF
  const char *stringa; // [rsp+50h] [rbp-10h]

  stringa = string;
  strcpy(vowels, "AEIOUaeiou");
  count = 0;
  memset(found, 0, sizeof(found));
  for ( i = 0; stringa[i]; ++i )
  {
    for ( j = 0; j < 10; ++j )
    {
      if ( stringa[i] == vowels[j] && !found[j] )
      {
        found[j] = 1;
        ++count;
        break;
      }
    }
  }
  if ( count < 5 )
    return (const char *)&unk_200F;
  else
    return "accepted";
}