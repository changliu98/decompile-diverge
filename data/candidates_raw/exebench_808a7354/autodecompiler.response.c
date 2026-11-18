void invert_mtx44(float *m)
{
 float t;
 float c;


 t = m[1];
 m[1] = m[4];
 m[4] = t;

 t = m[2];
 m[2] = m[8];
 m[8] = t;

 t = m[3];
 m[3] = m[12];
 m[12] = t;


 c = m[0] * m[13] + m[4] * m[14] + m[8] * m[15];

 t = m[13];
 m[13] = m[1] * m[12] + m[5] * m[14] + m[9] * m[15];
 m[14] = m[2] * m[12] + m[6] * m[14] + m[10] * m[15];
 m[15] = m[3] * m[12] + m[7] * m[14] + m[11] * m[15];


 m[12] = (*(unsigned int *)&c ^ 0x80000000);
 m[13] = (*(unsigned int *)&t ^ 0x80000000);
 m[14] = (*(unsigned int *)&m[14] ^ 0x80000000);
}