void
mlMatrixLoadPositionTransposedRotation(float *m, const float *p, const float *r)
{
 m[0] = r[0]; m[1] = r[4]; m[2] = r[8]; m[3] = 0.0f;
 m[4] = r[1]; m[5] = r[5]; m[6] = r[9]; m[7] = 0.0f;
 m[8] = r[2]; m[9] = r[6]; m[10] = r[10]; m[11] = 0.0f;
 m[12] = p[0]; m[13] = p[1]; m[14] = p[2]; m[15] = 1.0f;
}