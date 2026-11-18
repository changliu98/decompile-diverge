int __cdecl get_hex(char *buf, unsigned int *num)
{
  int done; // [rsp+0h] [rbp-18h]
  int cpos; // [rsp+4h] [rbp-14h]

  cpos = 0;
  done = 0;
  *num = 0;
  while ( !done )
  {
    if ( buf[cpos] < 48 || buf[cpos] > 57 )
    {
      if ( buf[cpos] < 65 || buf[cpos] > 70 )
      {
        if ( buf[cpos] < 97 || buf[cpos] > 102 )
        {
          done = 1;
        }
        else
        {
          *num *= 16;
          *num = buf[cpos] + *num - 97 + 10;
        }
      }
      else
      {
        *num *= 16;
        *num = buf[cpos] + *num - 65 + 10;
      }
    }
    else
    {
      *num *= 16;
      *num = buf[cpos] + *num - 48;
    }
    if ( !done )
      ++cpos;
    if ( cpos >= 8 )
      done = 1;
  }
  return cpos;
}