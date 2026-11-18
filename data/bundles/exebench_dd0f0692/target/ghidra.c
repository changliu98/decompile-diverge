void warp_mat4_fill_inverse(float *result,float *m)

{
  float fVar1;
  int i;
  float det;
  float inv [16];
  float *m_local;
  float *result_local;
  
  inv[0] = -(m[0xd] * m[7]) * m[10] +
           m[0xd] * m[6] * m[0xb] +
           m[9] * m[7] * m[0xe] +
           -(m[9] * m[6]) * m[0xf] + m[5] * m[10] * m[0xf] + -(m[5] * m[0xb] * m[0xe]);
  inv[4] = m[0xc] * m[7] * m[10] +
           -(m[0xc] * m[6]) * m[0xb] +
           -(m[8] * m[7]) * m[0xe] +
           m[8] * m[6] * m[0xf] + -m[4] * m[10] * m[0xf] + m[4] * m[0xb] * m[0xe];
  inv[8] = -(m[0xc] * m[7]) * m[9] +
           m[0xc] * m[5] * m[0xb] +
           m[8] * m[7] * m[0xd] +
           -(m[8] * m[5]) * m[0xf] + m[4] * m[9] * m[0xf] + -(m[4] * m[0xb] * m[0xd]);
  inv[0xc] = m[0xc] * m[6] * m[9] +
             -(m[0xc] * m[5]) * m[10] +
             -(m[8] * m[6]) * m[0xd] +
             m[8] * m[5] * m[0xe] + -m[4] * m[9] * m[0xe] + m[4] * m[10] * m[0xd];
  inv[1] = m[0xd] * m[3] * m[10] +
           -(m[0xd] * m[2]) * m[0xb] +
           -(m[9] * m[3]) * m[0xe] +
           m[9] * m[2] * m[0xf] + -m[1] * m[10] * m[0xf] + m[1] * m[0xb] * m[0xe];
  inv[5] = -(m[0xc] * m[3]) * m[10] +
           m[0xc] * m[2] * m[0xb] +
           m[8] * m[3] * m[0xe] +
           -(m[8] * m[2]) * m[0xf] + *m * m[10] * m[0xf] + -(*m * m[0xb] * m[0xe]);
  inv[9] = m[0xc] * m[3] * m[9] +
           -(m[0xc] * m[1]) * m[0xb] +
           -(m[8] * m[3]) * m[0xd] +
           m[8] * m[1] * m[0xf] + -*m * m[9] * m[0xf] + *m * m[0xb] * m[0xd];
  inv[0xd] = -(m[0xc] * m[2]) * m[9] +
             m[0xc] * m[1] * m[10] +
             m[8] * m[2] * m[0xd] +
             -(m[8] * m[1]) * m[0xe] + *m * m[9] * m[0xe] + -(*m * m[10] * m[0xd]);
  inv[2] = -(m[0xd] * m[3]) * m[6] +
           m[0xd] * m[2] * m[7] +
           m[5] * m[3] * m[0xe] +
           -(m[5] * m[2]) * m[0xf] + m[1] * m[6] * m[0xf] + -(m[1] * m[7] * m[0xe]);
  inv[6] = m[0xc] * m[3] * m[6] +
           -(m[0xc] * m[2]) * m[7] +
           -(m[4] * m[3]) * m[0xe] + m[4] * m[2] * m[0xf] + -*m * m[6] * m[0xf] + *m * m[7] * m[0xe]
  ;
  inv[10] = -(m[0xc] * m[3]) * m[5] +
            m[0xc] * m[1] * m[7] +
            m[4] * m[3] * m[0xd] +
            -(m[4] * m[1]) * m[0xf] + *m * m[5] * m[0xf] + -(*m * m[7] * m[0xd]);
  inv[0xe] = m[0xc] * m[2] * m[5] +
             -(m[0xc] * m[1]) * m[6] +
             -(m[4] * m[2]) * m[0xd] +
             m[4] * m[1] * m[0xe] + -*m * m[5] * m[0xe] + *m * m[6] * m[0xd];
  inv[3] = m[9] * m[3] * m[6] +
           -(m[9] * m[2]) * m[7] +
           -(m[5] * m[3]) * m[10] +
           m[5] * m[2] * m[0xb] + -m[1] * m[6] * m[0xb] + m[1] * m[7] * m[10];
  inv[7] = -(m[8] * m[3]) * m[6] +
           m[8] * m[2] * m[7] +
           m[4] * m[3] * m[10] + -(m[4] * m[2]) * m[0xb] + *m * m[6] * m[0xb] + -(*m * m[7] * m[10])
  ;
  inv[0xb] = m[8] * m[3] * m[5] +
             -(m[8] * m[1]) * m[7] +
             -(m[4] * m[3]) * m[9] + m[4] * m[1] * m[0xb] + -*m * m[5] * m[0xb] + *m * m[7] * m[9];
  inv[0xf] = -(m[8] * m[2]) * m[5] +
             m[8] * m[1] * m[6] +
             m[4] * m[2] * m[9] + -(m[4] * m[1]) * m[10] + *m * m[5] * m[10] + -(*m * m[6] * m[9]);
  fVar1 = m[3] * inv[0xc] + m[2] * inv[8] + *m * inv[0] + m[1] * inv[4];
  if ((fVar1 != 0.0) || (NAN(fVar1))) {
    fVar1 = DAT_00103004 / fVar1;
    for (i = 0; i < 0x10; i = i + 1) {
      result[i] = inv[i] * fVar1;
    }
  }
  return;
}