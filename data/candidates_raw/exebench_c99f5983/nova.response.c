void func0( vec3_t matrix[3] ){
	float temp;

	temp = matrix[1][0];
	matrix[1][0] = matrix[0][1];
	matrix[0][1] = temp;

	temp = matrix[1][2];
	matrix[1][2] = matrix[0][2];
	matrix[0][2] = temp;

	temp = matrix[2][0];
	matrix[2][0] = matrix[0][1];
	matrix[0][1] = temp;

	temp = matrix[2][1];
	matrix[2][1] = matrix[1][2];
	matrix[1][2] = temp;

	temp = matrix[2][2];
	matrix[2][2] = matrix[2][1];
	matrix[2][1] = temp;
}