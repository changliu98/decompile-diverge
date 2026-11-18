void geom_matmat2d( const vec3_t va, const vec3_t vb, vec3_t out ) {
	out[0] = va[1] * vb[2] - va[2] * vb[1];
	out[1] = va[2] * vb[0] - va[0] * vb[2];
	out[2] = va[0] * vb[1] - va[1] * vb[0];
}