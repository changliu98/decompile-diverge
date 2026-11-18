int __cdecl get_hex(char *buf, unsigned int *num)
{
  int cpos = 0;
  int done = 0;
  
  *num = 0;
  
  while ( !done )
  {
    char c = buf[cpos];

    if ( c >= '0' && c <= '9' )
    {
      *num = (*num * 16) + (c - '0');
    }
    else if ( c >= 'A' && c <= 'F' )
    {
      *num = (*num * 16) + (c - 'A' + 10);
    }
    else if ( c >= 'a' && c <= 'f' )
    {
      *num = (*num * 16) + (c - 'a' + 10);
    }
    else
    {
      done = 1;
    }

    if ( !done )
      ++cpos;
      
    if ( cpos >= 8 )
      done = 1;
  }
  
  return cpos;
}