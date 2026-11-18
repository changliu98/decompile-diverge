void mtxLoadScale(float mtx[16], float xScale, float yScale, float zScale)
{

    mtx[0] = xScale;
    mtx[5] = yScale;
    mtx[10] = zScale;


    mtx[15] = 1.0f;


    mtx[14] = 0.0f;
    mtx[13] = 0.0f;
    mtx[12] = 0.0f;
    mtx[11] = 0.0f;


    mtx[9] = 0.0f;
    mtx[8] = 0.0f;
    mtx[7] = 0.0f;
    mtx[6] = 0.0f;


    mtx[4] = 0.0f;
    mtx[3] = 0.0f;
    mtx[2] = 0.0f;
    mtx[1] = 0.0f;
}