void mac_real( picoVec2_t a, picoVec2_t b, picoVec2_t dest ){
	dest[ 0 ] = a[ 0 ] * b[ 0 ] + a[ 1 ] * b[ 1 ];
	dest[ 1 ] = a[ 0 ] * b[ 1 ] + a[ 1 ] * b[ 0 ];
}