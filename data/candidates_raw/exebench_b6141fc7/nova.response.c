void func0( vec3_t v, vec3_t matrix[3], vec3_t vec) {
	vec3_t tvec;

	VectorCopy( v, tvec );
	VectorMA( vec, -tvec[0], matrix[0], vec );
	VectorMA( vec, -tvec[1], matrix[1], vec );
	VectorMA( vec, -tvec[2], matrix[2], vec );
}