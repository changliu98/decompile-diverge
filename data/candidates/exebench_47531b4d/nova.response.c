void normalize_quat( vec3_t v ){
	int i;
	float length, ilength;

	length = v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ];
	length = ( float )sqrt( length );

	if ( length ) {
		ilength = 1.0 / length;
		for ( i = 0 ; i < 3 ; i++ ) {
			v[ i ] = v[ i ] * ilength;
		}
	}
}