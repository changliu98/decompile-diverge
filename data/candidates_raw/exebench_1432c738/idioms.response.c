void get_rotation_matrix(float a, float b, float *m)
{
  float a2; float a3;
  float b2; float b3;
  float ab2; float ab;
  int i;
  ab = a - b - 1.;
  ab2 = ab * ab;
  ab3 = ab2 * ab;
  a2 = a * a;
  a3 = a2 * a;
  b2 = b * b;
  b3 = b2 * b;
  m[0] = a * ab3 + a * ab2;
  m[1] = b * ab3 + b * ab2;
  m[8] = b * a3 + b * a2;
  m[11] = a * a3 + a * a2;
  m[9] = b * a2 * a + a * a2 * b;
  m[5] = a * a2 * a + b * a2 * b;
  m[2] = a * a2 * b * b + a * a2 * a * b + a * a2 * a * a
    + a * a * a * a * b * b * b + a * a * a * a * a * a * b * b
    + a * a * a * a * a * a * a * a * b * a
    + a * a * a * a * a * a * a * a * a * a * b
    + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a;
  m[4] = a * a * a * a * a * a * b * b + a * a * a * a * a * a * a * a * b * a
    + a * a * a * a * a * a * a * a * a * a * b
    + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * b * b + a * a * a * a * a * a * a * a * a * a * b
    + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * b * b + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * b * b;
  m[10] = a * a * a * a * a * a * a * a * a * a * b
    + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * b * b + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * b * b + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a * a * a * a * a * a * a
    + a * a * a * a * a * a * a