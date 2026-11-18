void ml_multiply_mat4_mat4(float *mat_a, float *mat_b, float *out)
{
  float temp1 = mat_a[0]*mat_b[0] + mat_a[1]*mat_b[4] + mat_a[2]*mat_b[8] + mat_a[3]*mat_b[12];
  float temp2 = mat_a[0]*mat_b[1] + mat_a[1]*mat_b[5] + mat_a[2]*mat_b[9] + mat_a[3]*mat_b[13];
  float temp3 = mat_a[0]*mat_b[2] + mat_a[1]*mat_b[6] + mat_a[2]*mat_b[10]+ mat_a[3]*mat_b[14];
  float temp4 = mat_a[0]*mat_b[3] + mat_a[1]*mat_b[7] + mat_a[2]*mat_b[11]+ mat_a[3]*mat_b[15];
  float temp5 = mat_a[4]*mat_b[0] + mat_a[5]*mat_b[4] + mat_a[6]*mat_b[8] + mat_a[7]*mat_b[12];
  float temp6 = mat_a[4]*mat_b[1] + mat_a[5]*mat_b[5] + mat_a[6]*mat_b[9] + mat_a[7]*mat_b[13];
  float temp7 = mat_a[4]*mat_b[2] + mat_a[5]*mat_b[6] + mat_a[6]*mat_b[10]+ mat_a[7]*mat_b[14];
  float temp8 = mat_a[4]*mat_b[3] + mat_a[5]*mat_b[7] + mat_a[6]*mat_b[11]+ mat_a[7]*mat_b[15];
  float temp9 = mat_a[8]*mat_b[0] + mat_a[9]*mat_b[4] + mat_a[10]*mat_b[8] + mat_a[11]*mat_b[12];
  float temp10 = mat_a[8]*mat_b[1] + mat_a[9]*mat_b[5] + mat_a[10]*mat_b[9] + mat_a[11]*mat_b[13];
  float temp11 = mat_a[8]*mat_b[2] + mat_a[9]*mat_b[6] + mat_a[10]*mat_b[10]+ mat_a[11]*mat_b[14];
  float temp12 = mat_a[8]*mat_b[3] + mat_a[9]*mat_b[7] + mat_a[10]*mat_b[11]+ mat_a[11]*mat_b[15];
  float temp13 = mat_a[12]*mat_b[0] + mat_a[13]*mat_b[4] + mat_a[14]*mat_b[8] + mat_a[15]*mat_b[12];
  float temp14 = mat_a[12]*mat_b[1] + mat_a[13]*mat_b[5] + mat_a[14]*mat_b[9] + mat_a[15]*mat_b[13];
  float temp15 = mat_a[12]*mat_b[2] + mat_a[13]*mat_b[6] + mat_a[14]*mat_b[10]+ mat_a[15]*mat_b[14];
  float temp16 = mat_a[12]*mat_b[3] + mat_a[13]*mat_b[7] + mat_a[14]*mat_b[11]+ mat_a[15]*mat_b[15];
  out[0] = mat_a[0]*mat_b[0] + mat_a[1]*mat_b[4] + mat_a[2]*mat_b[8] + mat_a[3]*mat_b[12];
  out[1] = temp1;
  out[2] = temp2;
  out[3] = temp3;
  out[4] = temp5;
  out[5] = temp6;
  out[6] = temp7;
  out[7] = temp8;
  out[8] = temp9;
  out[9] = temp10;
  out[10] = temp11;
  out[11] = temp12;
  out[12] = temp13;
  out[13] = temp14;
  out[14] = temp15;
  out[15] = temp16;
}