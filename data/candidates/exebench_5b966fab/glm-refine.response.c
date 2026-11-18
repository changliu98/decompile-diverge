void __cdecl load_inv(float *I, const float *M)
{
  float m0 = M[0];
  float m1 = M[1];
  float m2 = M[2];
  float m3 = M[3];
  float m4 = M[4];
  float m5 = M[5];
  float m6 = M[6];
  float m7 = M[7];
  float m8 = M[8];
  float m9 = M[9];
  float m10 = M[10];
  float m11 = M[11];
  float m12 = M[12];
  float m13 = M[13];
  float m14 = M[14];
  float m15 = M[15];

  float T = m5 * (m10 * m15 - m11 * m14) - m6 * (m9 * m15 - m11 * m13) + m7 * (m9 * m14 - m10 * m13);
  float T_4 = m4 * (m11 * m14 - m10 * m15) - m6 * (m15 * m8 - m11 * m12) + m7 * (m10 * m12 - m14 * m8);
  float T_8 = m4 * (m9 * m15 - m11 * m13) - m5 * (m15 * m8 - m11 * m12) + m7 * (m13 * m8 - m9 * m12);
  float T_12 = m4 * (m10 * m13 - m9 * m14) - m5 * (m14 * m8 - m10 * m12) + m6 * (m13 * m8 - m9 * m12);

  float T_16 = m1 * (m11 * m14 - m10 * m15) - m2 * (m15 * m8 - m11 * m12) + m3 * (m10 * m12 - m14 * m8);
  float T_20 = m0 * (m10 * m15 - m11 * m14) - m2 * (m9 * m15 - m11 * m13) + m3 * (m9 * m14 - m10 * m13);
  float T_24 = m0 * (m11 * m13 - m9 * m15) - m1 * (m15 * m8 - m11 * m12) + m3 * (m9 * m12 - m13 * m8);
  float T_28 = m0 * (m9 * m14 - m10 * m13) - m1 * (m14 * m8 - m10 * m12) + m2 * (m13 * m8 - m9 * m12);

  float T_32 = m1 * (m15 * m6 - m7 * m14) - m2 * (m15 * m5 - m7 * m13) + m3 * (m14 * m5 - m6 * m13);
  float T_36 = m0 * (m7 * m14 - m6 * m15) - m2 * (m7 * m12 - m15 * m4) + m3 * (m6 * m12 - m14 * m4);
  float T_40 = m0 * (m5 * m15 - m7 * m13) - m1 * (m7 * m12 - m15 * m4) + m3 * (m13 * m4 - m5 * m12);
  float T_44 = m0 * (m6 * m13 - m5 * m14) - m1 * (m14 * m4 - m6 * m12) + m2 * (m13 * m4 - m5 * m12);

  float T_48 = m1 * (m7 * m10 - m6 * m11) - m2 * (m7 * m8 - m5 * m11) + m3 * (m6 * m8 - m5 * m10);
  float T_52 = m0 * (m6 * m11 - m7 * m10) - m2 * (m5 * m11 - m7 * m9) + m3 * (m5 * m10 - m6 * m9);
  float T_56 = m0 * (m7 * m8 - m5 * m11) - m1 * (m7 * m9 - m5 * m11) + m3 * (m5 * m9 - m7 * m8);
  float T_60 = m0 * (m5 * m10 - m6 * m9) - m1 * (m6 * m8 - m5 * m10) + m2 * (m5 * m9 - m6 * m8);

  float d = m0 * T + m4 * T_16 + m8 * T_32 + m12 * T_48;

  I[0] = T / d;
  I[1] = T_16 / d;
  I[2] = T_32 / d;
  I[3] = T_48 / d;
  I[4] = T_4 / d;
  I[5] = T_20 / d;
  I[6] = T_36 / d;
  I[7] = T_52 / d;
  I[8] = T_8 / d;
  I[9] = T_24 / d;
  I[10] = T_40 / d;
  I[11] = T_56 / d;
  I[12] = T_12 / d;
  I[13] = T_28 / d;
  I[14] = T_44 / d;
  I[15] = T_60 / d;
}