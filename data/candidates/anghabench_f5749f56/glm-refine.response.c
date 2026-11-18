int __cdecl hex2int(int ch)
{
  // 'a' to 'f' -> 10 to 15
  if ( ch >= 'a' && ch <= 'f' )
    return ch - 'a' + 10;

  // 'A' to 'F' -> 10 to 15
  if ( ch >= 'A' && ch <= 'F' )
    return ch - 'A' + 10;

  // '0' to '9' -> 0 to 9
  // (Note: If ch is not a valid hex char, this will return garbage)
  return ch - '0';
}