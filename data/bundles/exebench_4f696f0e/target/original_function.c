void SwapIEEE32(char W[4])
{
   char B;

   B = W[0]; W[0] = W[3]; W[3] = B;
   B = W[1]; W[1] = W[2]; W[2] = B;
}