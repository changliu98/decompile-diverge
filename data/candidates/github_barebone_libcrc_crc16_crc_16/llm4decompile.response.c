uint16_t crc_16( const unsigned char *input_str, size_t num_bytes ) {

 uint16_t crc;
 uint16_t low_byte;
 uint16_t high_byte;
 const unsigned char *ptr;
 size_t a;

 if ( ! crc_tab16_init ) init_crc16_tab();

 crc = 0x0000;
 ptr = input_str;

 if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

  crc = (crc >> 8) ^ crc_tab16[ (crc ^ (uint16_t) *ptr++)&0x00FF ];
 }

 low_byte = (crc & 0xff00) >> 8;
 high_byte = (crc & 0x00ff);
 crc = low_byte | high_byte;

 return crc;

}