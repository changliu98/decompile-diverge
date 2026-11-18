void
mlMatrixLoadTransposedRotation(float m[16], float r[16])
{

 m[0] = r[0];
 m[1] = r[4];
 m[2] = r[8];

 m[4] = r[1];
 m[5] = r[5];
 m[6] = r[9];

 m[8] = r[2];
 m[9] = r[6];
 m[10] = r[10];
}