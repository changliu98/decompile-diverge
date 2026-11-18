void transpose(float (*mat)[4])
{
  int temp;
  temp = (*mat)[1];
  (*mat)[1] = (*mat)[4];
  (*mat)[4] = temp;
  temp = (*mat)[2];
  (*mat)[2] = (*mat)[8];
  (*mat)[8] = temp;
  temp = (*mat)[6];
  (*mat)[6] = (*mat)[9];
  (*mat)[9] = temp;
  (*mat)[12] = -((*mat)[12] * (*mat)[0] + (*mat)[13] * (*mat)[4] + (*mat)[14] * (*mat)[8]);
  (*mat)[13] = -((*mat)[12] * (*mat)[1] + (*mat)[13] * (*mat)[5] + (*mat)[14] * (*mat)[9]);
  (*mat)[14] = -((*mat)[12] * (*mat)[2] + (*mat)[13] * (*mat)[6] + (*mat)[14] * (*mat)[10]);
}