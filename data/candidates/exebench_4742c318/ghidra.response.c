float mayorDif(float *arrayLineal)

{
  float local_20;
  int i;
  float mayorTemp;
  float mayor;
  float *arrayLineal_local;
  
  mayor = 0.0;
  i = 0;
  while ((arrayLineal[i + 1] != 0.0 || (NAN(arrayLineal[i + 1])))) {
    local_20 = arrayLineal[i] - arrayLineal[i + 1];
    if (local_20 < 0.0) {
      local_20 = -local_20;
    }
    if (mayor < local_20) {
      mayor = local_20;
    }
    i = i + 1;
  }
  return mayor;
}