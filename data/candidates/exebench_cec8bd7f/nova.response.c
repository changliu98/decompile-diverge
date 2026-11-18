void cftf082(vec3_t v)
{
	float		max, scale;
	vec3_t		tempvec;

	
	VectorCopy( v, tempvec );
	max = abs( tempvec[0] );
	max = abs( tempvec[1] );
	max = abs( tempvec[2] );

	if (max == 0)
		max = 1;

	scale = 1.0f / max;

	tempvec[0] *= scale;
	tempvec[1] *= scale;
	tempvec[2] *= scale;

	VectorCopy( tempvec, v );
}