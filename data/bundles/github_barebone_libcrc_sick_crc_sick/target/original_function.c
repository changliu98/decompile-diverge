uint16_t crc_sick( const unsigned char *input_str, size_t num_bytes ) {

	uint16_t crc;
	uint16_t low_byte;
	uint16_t high_byte;
	uint16_t short_c;
	uint16_t short_p;
	const unsigned char *ptr;
	size_t a;

	crc     = CRC_START_SICK;
	ptr     = input_str;
	short_p = 0;

	if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

		short_c = 0x00FF & (uint16_t) *ptr;

		if ( crc & 0x8000 ) crc = ( crc << 1 ) ^ CRC_POLY_SICK;
		else                crc =   crc << 1;

		crc    ^= ( short_c | short_p );
		short_p = short_c << 8;

		ptr++;
	}

	low_byte  = (crc & 0xFF00) >> 8;
	high_byte = (crc & 0x00FF) << 8;
	crc       = low_byte | high_byte;

	return crc;

}