char *__cdecl func0(const char *text)
{
  char *result; // [rsp+8h] [rbp-28h]
  unsigned int j; // [rsp+14h] [rbp-1Ch]
  unsigned int i; // [rsp+18h] [rbp-18h]
  unsigned int crc; // [rsp+1Ch] [rbp-14h]
  unsigned int crca; // [rsp+1Ch] [rbp-14h]

  if ( !strlen(text) )
    return strdup("None");
  crc = -1;
  for ( i = 0; text[i]; ++i )
  {
    crc ^= (unsigned __int8)text[i];
    for ( j = 0; j < 8; ++j )
    {
      if ( (crc & 1) != 0 )
        crc = (crc >> 1) ^ 0xEDB88320;
      else
        crc >>= 1;
    }
  }
  crca = ~crc;
  result = (char *)malloc(9uLL);
  if ( result )
    sprintf(result, "%08X", crca);
  return result;
}