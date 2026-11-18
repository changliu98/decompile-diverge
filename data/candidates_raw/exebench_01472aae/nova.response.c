void func0(float *plane, float *xform, float *matrix)
{
	plane[0] = matrix[0];
	plane[1] = matrix[1];
	plane[2] = matrix[2];
	plane[3] = 0;
	plane[4] = matrix[4];
	plane[5] = matrix[5];
	plane[6] = matrix[6];
	plane[7] = 0;
	plane[8] = matrix[8];
	plane[9] = matrix[9];
	plane[10] = matrix[10];
	plane[11] = 0;
	plane[12] = -(matrix[12] * xform[0] + matrix[13] * xform[1] + matrix[14] * xform[2]);
	plane[13] = -(matrix[12] * xform[3] + matrix[13] * xform[4] + matrix[14] * xform[5]);
}