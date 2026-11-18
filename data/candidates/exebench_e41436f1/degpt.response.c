void htond(double *x)

{
  uint32_t uVar1;
  uint32_t uVar2;
  int Holding_Buffer;
  int *Double_Overlay;
  double *x_local;
  
  uVar2 = *(uint32_t *)x;
  uVar1 = htonl(*(uint32_t *)((long)x + 4));
  *(uint32_t *)x = uVar1;
  uVar2 = htonl(uVar2);
  *(uint32_t *)((long)x + 4) = uVar2;
  return;
}