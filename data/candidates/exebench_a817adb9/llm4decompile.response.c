void mtxScaleMatrix(float *matrix, float xScale, float yScale, float zScale)
{
    matrix[0] *= xScale;
    matrix[1] *= xScale;
    matrix[2] *= xScale;
    matrix[3] *= xScale;

    matrix[4] *= yScale;
    matrix[5] *= yScale;
    matrix[6] *= yScale;
    matrix[7] *= yScale;

    matrix[8] *= zScale;
    matrix[9] *= zScale;
    matrix[10] *= zScale;
    matrix[11] *= zScale;
}