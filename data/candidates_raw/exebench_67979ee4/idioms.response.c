void quat_mul(float q1[4], float q2[4], float q3[4])
{
  float q11 = q1[0]; float q12 = q1[1]; float q13 = q1[2]; float q14 = q1[3];
  float q21 = q2[0]; float q22 = q2[1]; float q23 = q2[2]; float q24 = q2[3];
  float q31 = q11 * q21 + q12 * q22 + q13 * q23 + q14 * q24;
  float q32 = q11 * q22 - q12 * q21 + q13 * q24 - q14 * q23;
  float q33 = q11 * q23 - q12 * q24 + q13 * q21 - q14 * q22;
  float q34 = q11 * q24 + q12 * q23 - q13 * q22 + q14 * q21;
  q3[0] = q31;
  q3[1] = q32;
  q3[2] = q33;
  q3[3] = q34;
}