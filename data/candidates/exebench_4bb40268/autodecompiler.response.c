void check_int(unsigned char input[1] , unsigned char output[1] )
{
  unsigned char state[1] ;
  unsigned char local1 ;

  {
  state[0UL] = (input[0UL] + 51238316UL) + (unsigned char)234;
  local1 = 0UL;
  while (local1 < 1UL) {
    if (state[0UL] < local1) {
      state[local1] = state[0UL] + state[0UL];
      state[0UL] += state[local1];
    } else {
      state[0UL] += state[0UL];
      state[local1] -= state[0UL];
    }
    if (state[0UL] == local1) {
      state[0UL] -= state[local1];
      state[local1] = state[0UL] + state[local1];
    } else {
      state[0UL] = state[local1] + state[0UL];
      state[local1] += state[local1];
    }
    local1 += 2UL;
  }
  output[0UL] = state[0UL] - (unsigned char)154;
}
}