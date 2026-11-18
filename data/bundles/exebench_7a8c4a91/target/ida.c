void __cdecl removeCharactersInPlace(char *aString, char *excludeChars)
{
  char v2; // [rsp+1h] [rbp-29h]
  char *excludePtr; // [rsp+2h] [rbp-28h]
  char found; // [rsp+11h] [rbp-19h]
  char *address; // [rsp+12h] [rbp-18h]
  char *aStringa; // [rsp+22h] [rbp-8h]

  aStringa = aString;
  address = aString;
  while ( *aStringa )
  {
    excludePtr = excludeChars;
    do
    {
      found = *aStringa == *excludePtr++;
      v2 = 0;
      if ( *excludePtr )
        v2 = ~found;
    }
    while ( (v2 & 1) != 0 );
    if ( (found & 1) == 0 )
      *address++ = *aStringa;
    ++aStringa;
  }
  *address = 0;
}