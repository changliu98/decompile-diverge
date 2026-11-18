void MatrixM(vec3_t v1, vec3_t v2) {
	int x, y, z;

	x = (int)(v1[0] * v2[0] + 0.5);
	y = (int)(v1[1] * v2[1] + 0.5);
	z = (int)(v1[2] * v2[2] + 0.5);

	v1[0] = x;
	v1[1] = y;
	v1[2] = z;
}