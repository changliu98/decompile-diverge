char *__cdecl func0(char *string)
{
  int i; // [rsp+10h] [rbp-20h]
  int hasOther; // [rsp+14h] [rbp-1Ch]
  int has1; // [rsp+18h] [rbp-18h]
  int has0; // [rsp+1Ch] [rbp-14h]

  has0 = 0;
  has1 = 0;
  hasOther = 0;
  for ( i = 0; i < strlen(string); ++i )
  {
    if ( string[i] == 48 )
    {
      has0 = 1;
    }
    else
    {
      if ( string[i] != 49 )
      {
        hasOther = 1;
        break;
      }
      has1 = 1;
    }
  }
  if ( (has0 || has1) && !hasOther )
    return (char *)&unk_2004;
  else
    return (char *)&unk_2008;
}