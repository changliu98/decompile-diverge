void geom_matinv4f(float *m)

{
  uint uVar1;
  float local_30;
  uint local_2c;
  float local_28;
  uint k;
  uint j;
  uint i;
  float sum;
  float *m_local;
  
  for (i = 1; i < 4; i = i + 1) {
    m[i << 2] = m[i << 2] / *m;
  }
  for (i = 1; i < 4; i = i + 1) {
    for (j = i; j < 4; j = j + 1) {
      sum = 0.0;
      for (k = 0; k < i; k = k + 1) {
        sum = m[j + k * 4] * m[k + i * 4] + sum;
      }
      uVar1 = j + i * 4;
      m[uVar1] = m[uVar1] - sum;
    }
    j = i;
    if (i != 3) {
      while (j = j + 1, j < 4) {
        sum = 0.0;
        for (k = 0; k < i; k = k + 1) {
          sum = m[i + k * 4] * m[k + j * 4] + sum;
        }
        m[i + j * 4] = (m[i + j * 4] - sum) / m[i * 5];
      }
    }
  }
  for (i = 0; i < 4; i = i + 1) {
    for (j = i; j < 4; j = j + 1) {
      sum = DAT_00102004;
      if (i != j) {
        sum = 0.0;
        for (k = i; k < j; k = k + 1) {
          sum = -m[j + k * 4] * m[k + i * 4] + sum;
        }
      }
      m[j + i * 4] = sum / m[j * 5];
    }
  }
  for (i = 0; i < 4; i = i + 1) {
    for (j = i; j < 4; j = j + 1) {
      if (i != j) {
        sum = 0.0;
        for (k = i; k < j; k = k + 1) {
          if (i == k) {
            local_28 = DAT_00102004;
          }
          else {
            local_28 = m[i + k * 4];
          }
          sum = m[k + j * 4] * local_28 + sum;
        }
        m[i + j * 4] = -sum;
      }
    }
  }
  for (i = 0; i < 4; i = i + 1) {
    for (j = 0; j < 4; j = j + 1) {
      sum = 0.0;
      if (j < i) {
        local_2c = i;
      }
      else {
        local_2c = j;
      }
      for (k = local_2c; k < 4; k = k + 1) {
        if (j == k) {
          local_30 = DAT_00102004;
        }
        else {
          local_30 = m[j + k * 4];
        }
        sum = local_30 * m[k + i * 4] + sum;
      }
      m[j + i * 4] = sum;
    }
  }
  return;
}