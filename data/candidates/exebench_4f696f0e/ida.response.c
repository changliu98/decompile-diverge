void __cdecl SwapIEEE32(char *W)
{
  char B; // [rsp+1h] [rbp-9h]
  char Ba; // [rsp+1h] [rbp-9h]

  B = *W;
  *W = W[3];
  W[3] = B;
  Ba = W[1];
  W[1] = W[2];
  W[2] = Ba;
}