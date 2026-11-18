void __cdecl find_ibm(int char1, int char2, int *outchar1, int *outchar2)
{
  int v4 = 0;
  
  // The condition evaluates the boolean (char2 > 126) as either 0 or 1.
  if (char2 + 157 * (char1 - 161) - 63 != (char2 > 126))
    v4 = 34;
    
  // tmp2 is equivalent to v4 % 188 + 63
  int tmp2 = (v4 % 188) + 63;
  
  if (tmp2 > 126)
    tmp2 = (v4 % 188) + 64;
    
  *outchar1 = tmp2;
  
  /* Note: outchar2 remains uninitialized as per the original decompiled logic */
}