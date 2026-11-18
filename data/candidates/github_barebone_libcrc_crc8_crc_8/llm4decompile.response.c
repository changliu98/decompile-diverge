uint8_t crc_8( const unsigned char *input_str, size_t num_bytes ) {

 size_t a;
 uint8_t crc;
 const unsigned char *ptr;

 crc = 0x00;
 ptr = input_str;

 if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

  crc = sht75_crc_table[(*ptr++) ^ crc];
 }

 return crc;

}