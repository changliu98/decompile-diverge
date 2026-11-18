int __cdecl stringToInt(unsigned int *val, const char *buff)
{
  *val = 0;
  while ( *buff )
  {
    if ( *buff < 48 || *buff > 57 )
      return -1;
    *val = *buff++ + 10 * *val - 48;
  }
  return 0;
}