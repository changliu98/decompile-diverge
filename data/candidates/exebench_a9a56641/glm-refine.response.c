void __cdecl Mat4_inv_Mat4_affine_mul(float *result, float *src1, float *src2)
{
  // Precompute the negated translation components of src1
  float neg_src1_2  = -(src1[2]  * src1[14] + src1[0] * src1[12] + src1[1]  * src1[13]);
  float neg_src1_6  = -(src1[6]  * src1[14] + src1[4] * src1[12] + src1[5]  * src1[13]);
  float neg_src1_10 = -(src1[10] * src1[14] + src1[8] * src1[12] + src1[9]  * src1[13]);

  // Row 0
  result[0]  = src1[0] * src2[0]  + src1[1] * src2[1]  + src1[2]  * src2[2];
  result[1]  = src1[4] * src2[0]  + src1[5] * src2[1]  + src1[6]  * src2[2];
  result[2]  = src1[8] * src2[0]  + src1[9] * src2[1]  + src1[10] * src2[2];
  result[3]  = 0.0f;

  // Row 1
  result[4]  = src1[0] * src2[4]  + src1[1] * src2[5]  + src1[2]  * src2[6];
  result[5]  = src1[4] * src2[4]  + src1[5] * src2[5]  + src1[6]  * src2[6];
  result[6]  = src1[8] * src2[4]  + src1[9] * src2[5]  + src1[10] * src2[6];
  result[7]  = 0.0f;

  // Row 2
  result[8]  = src1[0] * src2[8]  + src1[1] * src2[9]  + src1[2]  * src2[10];
  result[9]  = src1[4] * src2[8]  + src1[5] * src2[9]  + src1[6]  * src2[10];
  result[10] = src1[8] * src2[8]  + src1[9] * src2[9]  + src1[10] * src2[10];
  result[11] = 0.0f;

  // Row 3
  result[12] = src1[0] * src2[12] + src1[1] * src2[13] + src1[2]  * src2[14] + neg_src1_2;
  result[13] = src1[4] * src2[12] + src1[5] * src2[13] + src1[6]  * src2[14] + neg_src1_6;
  result[14] = src1[8] * src2[12] + src1[9] * src2[13] + src1[10] * src2[14] + neg_src1_10;
  result[15] = 1.0f;
}