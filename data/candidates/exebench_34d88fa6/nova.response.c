void mlMatrixMultVectorTo( const m4x4_t matrix, const vec3_t translation, vec3_t euler ){
	euler[0] = matrix[1] * matrix[5] - matrix[2] * matrix[4];
	euler[1] = matrix[2] * matrix[3] - matrix[1] * matrix[6];
	euler[2] = matrix[1] * matrix[4] - matrix[2] * matrix[3];

	euler[0] = RAD2DEG(euler[0]);
	euler[1] = RAD2DEG(euler[1]);
	euler[2] = RAD2DEG(euler[2]);
}