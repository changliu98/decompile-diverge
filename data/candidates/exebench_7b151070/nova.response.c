void Mat4_RotateQuaternion(vec4_t v, vec4_t m) {
	vec4_t t;
	t[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
	t[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
	t[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
	t[3] = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];
	VectorCopy(t, v);
}