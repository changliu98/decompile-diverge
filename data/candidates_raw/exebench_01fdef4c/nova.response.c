void func0( tcMod_t mod ){
	float m00, m01, m02, m10, m11, m12;

	m00 = mod[ 0 ][ 0 ];
	m01 = mod[ 1 ][ 0 ];
	m02 = mod[ 2 ][ 0 ];
	m10 = mod[ 0 ][ 1 ];
	m11 = mod[ 1 ][ 1 ];
	m12 = mod[ 2 ][ 1 ];

	mod[ 0 ][ 0 ] += mod[ 0 ][ 2 ];
	mod[ 1 ][ 0 ] += mod[ 1 ][ 2 ];
	mod[ 2 ][ 0 ] += mod[ 2 ][ 2 ];

	mod[ 0 ][ 1 ] -= mod[ 0 ][ 2 ];
	mod[ 1 ][ 1 ] -= mod[ 1 ][ 2 ];
	mod[ 2 ][ 1 ] -= mod[ 2 ][ 2 ];

	mod[ 0 ][ 2 ] = m00 - mod[ 0 ][ 0 ];
	mod[ 1 ][ 2 ] = m01 - mod[ 1 ][ 0 ];
	mod[ 2 ][ 2 ] = m02 - mod[ 2 ][ 0 ];

	mod[ 0 ][ 3 ] += m02 - m00;
	mod[ 1 ][ 3 ] += m12 - m10;
	mod[ 2 ][ 3 ] += m22 - m20;
}