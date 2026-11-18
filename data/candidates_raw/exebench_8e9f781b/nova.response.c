void func0( tcMod_t mod ){
	float m00, m01, m02, m10, m11, m12;

	m00 = mod[ 0 ];
	m01 = mod[ 1 ];
	m02 = mod[ 2 ];
	m10 = mod[ 3 ];
	m11 = mod[ 4 ];
	m12 = mod[ 5 ];

	mod[ 0 ] = m00 + mod[ 6 ];
	mod[ 1 ] = m01 + mod[ 7 ];
	mod[ 2 ] = m02 + mod[ 8 ];
	mod[ 3 ] = m10 + mod[ 9 ];
	mod[ 4 ] = m11 + mod[ 10 ];
	mod[ 5 ] = m12 + mod[ 11 ];

	mod[ 6 ] = m00 - mod[ 6 ];
	mod[ 7 ] = m01 - mod[ 7 ];
	mod[ 8 ] = m02 - mod[ 8 ];
	mod[ 9 ] = m10 - mod[ 9 ];
	mod[ 10 ] = m11 - mod[ 10 ];
	mod[ 11 ] = m12 - mod[ 11 ];
}