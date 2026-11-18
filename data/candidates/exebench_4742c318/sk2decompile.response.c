float mayorDif(float *v) {
  int i;
  float dif, mayor, mod;
  mayor = 0;
  for (i = 0; v[i + 1] != 0; i++) {
    dif = v[i] - v[i + 1];
    mod = (dif < 0) ? -dif : dif;
    if (mod > mayor) mayor = mod;
  }
  return mayor;
}