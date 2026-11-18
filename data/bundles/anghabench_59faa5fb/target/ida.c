void __cdecl scsi_sanitize_inquiry_string(unsigned __int8 *s, int len)
{
  int terminated; // [rsp+0h] [rbp-10h]

  terminated = 0;
  while ( len > 0 )
  {
    if ( !*s )
      terminated = 1;
    if ( terminated || *s < 0x20u || *s > 0x7Eu )
      *s = 32;
    --len;
    ++s;
  }
}