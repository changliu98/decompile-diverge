void mtxScaleMatrix(float *matrix, float scaleX, float scaleY, float scaleZ)
{
    // Scale the first column (X-axis components) by xScale
    *matrix = scaleX * *matrix;       // mtx[0]
    matrix[4] = scaleX * matrix[4];   // mtx[4]
    matrix[8] = scaleX * matrix[8];   // mtx[8]
    matrix[0xc] = scaleX * matrix[0xc]; // mtx[12]

    // Scale the second column (Y-axis components) by yScale
    matrix[1] = scaleY * matrix[1];   // mtx[1]
    matrix[5] = scaleY * matrix[5];   // mtx[5]
    matrix[9] = scaleY * matrix[9];   // mtx[9]
    matrix[0xd] = scaleY * matrix[0xd]; // mtx[13]

    // Scale the third column (Z-axis components) by zScale
    matrix[2] = scaleZ * matrix[2];   // mtx[2]
    matrix[6] = scaleZ * matrix[6];   // mtx[6]
    matrix[10] = scaleZ * matrix[10]; // mtx[10]
    matrix[0xe] = scaleZ * matrix[0xe]; // mtx[14]
}