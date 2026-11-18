void RandomFunc(unsigned char input[1] , unsigned char output[1] )
{
  unsigned char state[1] ;
  unsigned char local1 ;

  {
  state[0UL] = (input[0UL] + 914778474UL) - (unsigned char)183;
  local1 = 0UL;
  while (local1 < 1UL) {
    if (state[0UL] < local1) {
      state[local1] = state[0UL] + state[local1];
      state[0UL] = state[local1] - state[0UL];
    } else {
      state[local1] = state[0UL] + state[local1];
      state[local1] += state[local1];
    }
    if (state[0UL] == local1) {
      state[0UL] += state[local1];
      state[0UL] += state[0UL];
    } else {
      state[0UL] -= state[local1];
      state[local1] += state[0UL];
    }
    local1 ++;
  }
  output[0UL] = (state[0UL] + 238420169UL) + (unsigned char)127;
}
}