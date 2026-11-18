void f(unsigned char input[1] , unsigned char output[1] )
{
  unsigned char state[1] ;
  unsigned char local1 ;

  {
  state[0UL] = (input[0UL] & 914778474UL) << (unsigned char)7;
  local1 = 0UL;
  while (local1 < (unsigned char)0) {
    if (state[0UL] > local1) {
      state[local1] = state[0UL] << (((state[0UL] >> (unsigned char)1) & (unsigned char)7) | 1UL);
    } else {
      state[local1] = state[0UL] << (((state[local1] >> (unsigned char)4) & (unsigned char)7) | 1UL);
    }
    local1 ++;
  }
  output[0UL] = (state[0UL] & 218093449UL) | (unsigned char)206;
}
}