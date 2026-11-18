void RandomFunc(unsigned char input[1] , unsigned long long *state )
{
  unsigned long long local1 ;
  unsigned long long local2 ;
  unsigned long long local3 ;
  unsigned long long local4 ;
  unsigned long long local5 ;
  unsigned long long local6 ;

  {
  state[0UL] = (unsigned long long )0;
  local1 = (unsigned long long )0;
  while (local1 < 1UL) {
    local2 = (unsigned long long )0;
    while (local2 < 1UL) {
      if (state[0UL] == local2) {
        state[local1] = state[0UL] + state[local1];
        local3 = state[0UL] - state[local1];
      } else {
        state[local1] += state[local2];
        local4 = state[local2] - state[0UL];
      }
      local2 ++;
    }
    local1 += 2UL;
  }
  local5 = (unsigned long long )0;
  while (local5 < 1UL) {
    local6 = (unsigned long long )0;
    while (local6 < 1UL) {
      input[0UL] = (input[0UL] + input[0UL]) - (unsigned char )(state[0UL] == local6);
      local6 ++;
    }
    local5 ++;
  }
}
}