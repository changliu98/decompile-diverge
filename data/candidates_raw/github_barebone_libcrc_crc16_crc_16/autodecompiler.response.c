unsigned short crc_modbus( unsigned char *pcBlock, unsigned long len )
{
 unsigned short crc;
 unsigned long i;

 if ( !( crc_tab16_init & 1 ) )
 {
  init_crc16_tab();
 }

 crc = 0x0000;
 pcBlock = (unsigned char *)pcBlock;

 if ( pcBlock != NULL )
 {
  for ( i = 0; i < len; i++ )
  {
   crc = ( crc >> 8 ) ^ crc_tab16[ (crc ^ (unsigned short) *pcBlock++) & 0x00FF ];
  }
 }

 return crc;
}