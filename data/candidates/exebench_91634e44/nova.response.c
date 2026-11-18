void qtomat( const vec3_t in, vec3_t out ) {
	out[0] = in[0] * in[0] - in[1] * in[1] + in[2] * in[2];
	out[1] = in[1] * in[0] + in[0] * in[1] - in[2] * in[2];
	out[2] = in[2] * in[0] + in[1] * in[2] + in[0] * in[1];
	out[3] = in[1] * in[2] - in[0] * in[2] + in[0] * in[1];
	out[4] = in[0] * in[2] - in[1] * in[2] + in[0] * in[2];
	out[5] = in[0] * in[1] - in[0] * in[2] + in[1] * in[2];
	out[6] = in[1] * in[2] - in[0] * in[1] + in[0] * in[2];
	out[7] = in[0] * in[1] - in[0] * in[2] + in[1] * in[2];
	out[8] = in[0] * in[0] - in[1] * in[1] - in[2] * in[2];
}