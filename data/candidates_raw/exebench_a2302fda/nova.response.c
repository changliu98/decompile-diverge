void func0( tcMod_t mod ){
	float matrix[3][3];
	float temp[3];

	matrix[0][0] = mod[0][0]; matrix[0][1] = mod[0][1]; matrix[0][2] = mod[0][2];
	matrix[1][0] = mod[1][0]; matrix[1][1] = mod[1][1]; matrix[1][2] = mod[1][2];
	matrix[2][0] = mod[2][0]; matrix[2][1] = mod[2][1]; matrix[2][2] = mod[2][2];

	temp[0] = matrix[0][0] + matrix[1][0];
	temp[1] = matrix[0][1] + matrix[1][1];
	matrix[0][0] = temp[0];
	matrix[0][1] = temp[1];
	temp[0] = matrix[0][0] - matrix[1][0];
	temp[1] = matrix[0][1] - matrix[1][1];
	matrix[1][0] = temp[0];
	matrix[1][1] = temp[1];

	temp[0] = matrix[2][0] + matrix[1][0];
	temp[1] = matrix[2][1] + matrix[1][1];
	matrix[2][0] = temp[0];
	matrix[2][1] = temp[1];
	temp[0] = matrix[2][0] - matrix[1][0];
	temp[1] = matrix[2][1] - matrix[1][1];
	matrix[1][0] = temp[0];
	matrix[1][1] = temp[1];

	mod[0][0] = matrix[0][0]; mod[0][1] = matrix[0][1]; mod[0][2] = matrix[0][2];
	mod[1][0] = matrix[1][0]; mod[1][1] = matrix[1][1]; mod[1][2] = matrix[1][2];
	mod[2][0] = matrix[