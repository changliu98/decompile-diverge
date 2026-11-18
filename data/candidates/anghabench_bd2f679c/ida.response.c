void __cdecl crc8_byte(unsigned int *crc, unsigned __int8 db)
{
  int f; // [rsp+0h] [rbp-14h]
  int i; // [rsp+4h] [rbp-10h]

  for ( i = 0; i < 8; ++i )
  {
    f = (db ^ (unsigned __int8)*crc) & 1;
    *crc >>= 1;
    db = (int)db >> 1;
    if ( f )
      *crc ^= 0x8Cu;
  }
  *crc = (unsigned __int8)*crc;
}