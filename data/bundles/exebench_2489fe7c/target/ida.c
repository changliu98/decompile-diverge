void __cdecl crc16_b(unsigned int *crc, unsigned __int8 db)
{
  int i; // [rsp+0h] [rbp-10h]

  for ( i = 0; i < 8; ++i )
  {
    *crc *= 2;
    if ( (((unsigned __int8)BYTE2(*crc) ^ db) & 1) != 0 )
      *crc ^= 0x8005u;
    db = (int)db >> 1;
  }
  *crc = (unsigned __int16)*crc;
}