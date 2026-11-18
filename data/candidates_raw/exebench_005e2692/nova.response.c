void func0( const vec2_t va, const vec2_t vb, vec2_t out ) {
	out[0] = va[0] * vb[0] + va[1] * vb[1];
	out[1] = va[2] * vb[0] + va[3] * vb[1];
}