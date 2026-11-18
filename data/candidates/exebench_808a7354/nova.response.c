void Mat4_affine_inv( mat4_t matrix ){
	float temp;

	temp = -( matrix[3] );
	matrix[3] = matrix[12];
	matrix[12] = matrix[3];
	matrix[3] = temp;

	temp = -( matrix[7] );
	matrix[7] = matrix[13];
	matrix[13] = matrix[7];
	matrix[7] = temp;

	temp = -( matrix[11] );
	matrix[11] = matrix[14];
	matrix[14] = matrix[11];
	matrix[11] = temp;

	temp = matrix[0];
	matrix[0] = matrix[4];
	matrix[4] = matrix[1];
	matrix[1] = matrix[5];
	matrix[5] = temp;

	matrix[0] = -( matrix[0] );
	matrix[5] = -( matrix[5] );
	matrix[10] = -( matrix[10] );
}