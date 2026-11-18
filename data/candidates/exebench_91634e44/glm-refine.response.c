void __cdecl qtomat(float *q, float *rot)
{
  float q0 = q[0];
  float q1 = q[1];
  float q2 = q[2];
  float q3 = q[3];

  // The bitwise XOR with 0x80000000 on a float is equivalent to flipping its sign bit.
  // The decompiled SSE intrinsics simply compute products and negate them.
  
  rot[0] = (q0 * q0) + (q1 * q1) - (q2 * q2) - (q3 * q3);
  rot[1] = 2.0f * (q1 * q2 - q0 * q3);
  rot[2] = 2.0f * (q1 * q3 + q0 * q2);
  
  rot[3] = 2.0f * (q1 * q2 + q0 * q3);
  rot[4] = (q0 * q0) - (q1 * q1) + (q2 * q2) - (q3 * q3);
  rot[5] = 2.0f * (q2 * q3 - q0 * q1);
  
  rot[6] = 2.0f * (q1 * q3 - q0 * q2);
  rot[7] = 2.0f * (q2 * q3 + q0 * q1);
  rot[8] = (q0 * q0) - (q1 * q1) - (q2 * q2) + (q3 * q3);
}