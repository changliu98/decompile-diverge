void func0( vec3_t va, vec3_t vb ){
	float		d;

	d = DotProduct( va, vb );
	va[0] += d * vb[0];
	va[1] += d * vb[1];
	va[2] += d * vb[2];
}