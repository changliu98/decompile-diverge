void __cdecl mlMatrixLoadTransposedRotation(float *m, const float *r)
{
  // Row 0 of destination = Column 0 of source
  m[0]  = r[0];
  m[1]  = r[4];
  m[2]  = r[8];
  // m[3]  = 0.0f;

  // Row 1 of destination = Column 1 of source
  m[4]  = r[1];
  m[5]  = r[5];
  m[6]  = r[9];
  // m[7]  = 0.0f;

  // Row 2 of destination = Column 2 of source
  m[8]  = r[2];
  m[9]  = r[6];
  m[10] = r[10];
  // m[11] = 0.0f;

  // Row 3 of destination (Translation/Homogeneous)
  // m[12] = 0.0f;
  // m[13] = 0.0f;
  // m[14] = 0.0f;
  // m[15] = 1.0f;
}