void __cdecl wdc_UtilsDeleteCharFromString(char *buffer, int buffSize, char charToRemove)
{
  int v3; // ecx
  bool v4; // [rsp+1h] [rbp-19h]
  int count; // [rsp+2h] [rbp-18h]
  int i; // [rsp+6h] [rbp-14h]

  count = 0;
  if ( buffer && buffSize )
  {
    for ( i = 0; ; ++i )
    {
      v4 = 0;
      if ( i < buffSize )
        v4 = buffer[i] != 0;
      if ( !v4 )
        break;
      if ( buffer[i] != charToRemove )
      {
        v3 = count++;
        buffer[v3] = buffer[i];
      }
    }
    buffer[count] = 0;
  }
}