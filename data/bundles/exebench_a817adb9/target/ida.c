void __cdecl mtxScaleMatrix(float *mtx, float xScale, float yScale, float zScale)
{
  *mtx = xScale * *mtx;
  mtx[4] = xScale * mtx[4];
  mtx[8] = xScale * mtx[8];
  mtx[12] = xScale * mtx[12];
  mtx[1] = yScale * mtx[1];
  mtx[5] = yScale * mtx[5];
  mtx[9] = yScale * mtx[9];
  mtx[13] = yScale * mtx[13];
  mtx[2] = zScale * mtx[2];
  mtx[6] = zScale * mtx[6];
  mtx[10] = zScale * mtx[10];
  mtx[14] = zScale * mtx[14];
}