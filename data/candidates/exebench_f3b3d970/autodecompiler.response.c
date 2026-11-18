void bitrv208(double *mat)
{
 double temp[4];
 temp[0] = mat[2]; temp[1] = mat[3];
 temp[2] = mat[6]; temp[3] = mat[7];
 temp[4] = mat[8]; temp[5] = mat[9];
 temp[6] = mat[12]; temp[7] = mat[13];

 mat[2] = mat[8]; mat[3] = mat[9];
 mat[6] = mat[12]; mat[7] = mat[13];
 mat[8] = temp[0]; mat[9] = temp[1];
 mat[12] = temp[2]; mat[13] = temp[3];
}