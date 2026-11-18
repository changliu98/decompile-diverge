char *__cdecl intToString(char *buff, unsigned int val)
{
  int i; // [rsp+0h] [rbp-10h]

  buff[9] = 0;
  for ( i = 8; i >= 0; --i )
  {
    buff[i] = val % 0xA + 48;
    val /= 0xAu;
    if ( !val )
      break;
  }
  return &buff[i];
}