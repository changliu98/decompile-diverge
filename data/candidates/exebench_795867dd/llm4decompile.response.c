void geom_matinv4f(float *m)
{
 unsigned i, j, k;
 float det, detinv;
 float m2[16];

 for(i = 1; i < 4; i++)
  m[4 * i] /= m[0];

 for(i = 1; i < 4; i++) {
  for(j = i; j < 4; j++) {
   det = 0.0f;
   for(k = 0; k < i; k++)
    det += m[4 * j + k] * m[4 * i + k];
   m[4 * j + i] -= det;
  }
  if(i == 3)
   continue;
  detinv = 1.0f / m[4 * i + i];
  for(j = i + 1; j < 4; j++) {
   det = 0.0f;
   for(k = 0; k < i; k++)
    det += m[4 * i + k] * m[4 * j + k];
   m[4 * i + j] = (m[4 * i + j] - det) * detinv;
  }
 }

 for(i = 0; i < 4; i++) {
  for(j = i; j < 4; j++) {
   det = (i == j) ? 1.0f : 0.0f;
   for(k = i; k < j; k++)
    det -= m[4 * j + k] * m[4 * i + k];
   m[4 * i + j] = det / m[4 * j + j];
  }
 }

 for(i = 0; i < 4; i++) {
  for(j = i; j < 4; j++) {
   if(i == j)
    continue;
   det = 0.0f;
   for(k = i; k < j; k++)
    det += (i == k) ? m[4 * j + k] : (m[4 * i + k] * m[4 * j + k]);
   m[4 * i + j] = -det;
  }
 }

 for(i = 0; i < 4; i++) {
  for(j = 0; j < 4; j++) {
   det = 0.0f;
   for(k = ((i) > (j) ? (i) : (j)); k < 4; k++)
    det += (j == k) ? m[4 * i + k] : (m[4 * j + k] * m[4 * i + k]);
   m2[4 * j + i] = det;
  }
 }

 for(i = 0; i < 4; i++) {
  for(j = 0; j < 4; j++) {
   m[4 * j + i] = m2[4 * j + i];
  }
 }
}