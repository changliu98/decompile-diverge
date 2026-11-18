void __cdecl breakup(short *fcs_bit, unsigned __int16 usps_crc)
{
  int i; // [rsp+0h] [rbp-10h]
  unsigned __int16 usps_crca; // [rsp+6h] [rbp-Ah]

  usps_crca = usps_crc;
  for ( i = 0; i < 13; ++i )
    fcs_bit[i] = 0;
  if ( usps_crc >= 0x1000u )
  {
    fcs_bit[12] = 1;
    usps_crca = usps_crc - 4096;
  }
  if ( usps_crca >= 0x800u )
  {
    fcs_bit[11] = 1;
    usps_crca -= 2048;
  }
  if ( usps_crca >= 0x400u )
  {
    fcs_bit[10] = 1;
    usps_crca -= 1024;
  }
  if ( usps_crca >= 0x200u )
  {
    fcs_bit[9] = 1;
    usps_crca -= 512;
  }
  if ( usps_crca >= 0x100u )
  {
    fcs_bit[8] = 1;
    usps_crca -= 256;
  }
  if ( usps_crca >= 0x80u )
  {
    fcs_bit[7] = 1;
    usps_crca -= 128;
  }
  if ( usps_crca >= 0x40u )
  {
    fcs_bit[6] = 1;
    usps_crca -= 64;
  }
  if ( usps_crca >= 0x20u )
  {
    fcs_bit[5] = 1;
    usps_crca -= 32;
  }
  if ( usps_crca >= 0x10u )
  {
    fcs_bit[4] = 1;
    usps_crca -= 16;
  }
  if ( usps_crca >= 8u )
  {
    fcs_bit[3] = 1;
    usps_crca -= 8;
  }
  if ( usps_crca >= 4u )
  {
    fcs_bit[2] = 1;
    usps_crca -= 4;
  }
  if ( usps_crca >= 2u )
  {
    fcs_bit[1] = 1;
    usps_crca -= 2;
  }
  if ( usps_crca == 1 )
    *fcs_bit = 1;
}