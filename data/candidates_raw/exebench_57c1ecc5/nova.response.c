void func0( vec3_t v ){
	float	x, y, z;
	float	min, max, range;

	x = v[ 0 ];
	y = v[ 1 ];
	z = v[ 2 ];

	min = x < y? ( x < z? x : z ) : ( y < z? y : z );
	max = x > y? ( x > z? x : z ) : ( y > z? y : z );
	range = max - min;

	x = ( x - min ) / range;
	y = ( y - min ) / range;
	z = ( z - min ) / range;

	v[ 0 ] = x;
	v[ 1 ] = y;
	v[ 2 ] = z;
}