void zero_poly(int *poly)

{
  int i;
  int *poly_local;
  
  for (i = 0; i < 0x14; i = i + 1) {
    poly[i] = 0;
  }
  return;
}