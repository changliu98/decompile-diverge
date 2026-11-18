unsigned short crc_kermit( const unsigned char *input_str, size_t num_bytes ) {

 unsigned short crc;
 const unsigned char *ptr;
 size_t a;

 if ( ! crc_tab_init ) init_crc_tab();

 crc = 0x0000;
 ptr = input_str;

 if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

  crc = (crc >> 8) ^ crc_tab[ (crc ^ (unsigned char) *ptr++) & 0x00FF ];
 }

 crc = (crc >> 8) | (crc << 8);

 return crc;

}