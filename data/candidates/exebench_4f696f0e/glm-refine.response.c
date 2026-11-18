void __cdecl SwapIEEE32(char *W)
{
  char temp0; 
  char temp1; 

  // Swap byte 0 and byte 3
  temp0 = *W;
  *W = W[3];
  W[3] = temp0;
  
  // Swap byte 1 and byte 2
  temp1 = W[1];
  W[1] = W[2];
  W[2] = temp1;
}