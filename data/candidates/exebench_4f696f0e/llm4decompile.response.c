void SwapIEEE32(char *W)
{
   char T;

   T = W[0]; W[0] = W[3]; W[3] = T;
   T = W[1]; W[1] = W[2]; W[2] = T;
}