void func0(vec3_t v) {
	vec3_t v2;
	float t;

	VectorCopy(v, v2);

	t = v2[0];
	v2[0] = v2[2];
	v2[2] = t;

	t = v2[1];
	v2[1] = v2[2];
	v2[2] = t;

	t = v2[0];
	v2[0] = v2[1];
	v2[1] = t;

	VectorCopy(v2, v);
}