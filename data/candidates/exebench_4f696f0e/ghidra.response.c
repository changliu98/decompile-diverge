void SwapIEEE32(char *W)

{
  char cVar1;
  char B;
  char *W_local;
  
  cVar1 = *W;
  *W = W[3];
  W[3] = cVar1;
  cVar1 = W[1];
  W[1] = W[2];
  W[2] = cVar1;
  return;
}