void func0( const vec4_t in1, const vec4_t in2, vec4_t out ) {
	out[0] = in1[0] * in2[0] + in1[1] * in2[2];
	out[1] = in1[0] * in2[1] + in1[1] * in2[3];
	out[2] = in1[2] * in2[0] + in1[3] * in2[2];
	out[3] = in1[2] * in2[1] + in1[3] * in2[3];
}