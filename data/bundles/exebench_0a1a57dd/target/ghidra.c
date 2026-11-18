void htonf(float *x)

{
  float fVar1;
  int Holding_Buffer;
  int *Float_Overlay;
  float *x_local;
  
  fVar1 = (float)htonl((uint32_t)*x);
  *x = fVar1;
  return;
}