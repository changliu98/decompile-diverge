void geom_matinv4f(float *m) {
  unsigned int i, j, k;
  float s;
  for (i = 1; i < 4; i++) m[i] /= m[0];
  for (i = 1; i < 4; i++) {
    for (j = i; j < 4; j++) {
      s = 0.0f;
      for (k = 0; k < i; k++) s += m[k + i * 4] * m[k + j * 4];
      m[j + i * 4] -= s;
    }
    if (i != 3) {
      for (j = i + 1; j < 4; j++) {
        s = 0.0f;
        for (k = 0; k < i; k++) s += m[k + i * 4] * m[k + j * 4];
        m[j + i * 4] = (m[j + i * 4] - s) / m[i * 5];
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = i; j < 4; j++) {
      s = 1.0f;
      if (i != j) {
        s = 0.0f;
        for (k = i; k < j; k++) s -= m[k + i * 4] * m[k + j * 4];
      }
      m[j + i * 4] = s / m[j * 5];
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = i; j < 4; j++) {
      if (i != j) {
        s = 0.0f;
        for (k = i; k < j; k++)
          s += (k == i ? 1.0f : m[k + i * 4]) * m[k + j * 4];
        m[j + i * 4] = -s;
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      s = 0.0f;
      for (k = (i > j ? i : j); k < 4; k++)
        s += (j == k ? 1.0f : m[k + j * 4]) * m[k + i * 4];
      m[j + i * 4] = s;
    }
  }
}