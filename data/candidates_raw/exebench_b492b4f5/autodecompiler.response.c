void RandomFunc(unsigned int input[1] , unsigned int output[1] )
{
  unsigned int state[1] ;
  unsigned int local1 ;
  unsigned short copy11 ;

  {
  state[0UL] = (input[0UL] & 914778474UL) << 7U;
  local1 = 0UL;
  while (local1 < 1UL) {
    if (state[0UL] > local1) {
      copy11 = *((unsigned short *)(& state[local1]) + 1);
      *((unsigned short *)(& state[local1]) + 1) = *((unsigned short *)(& state[local1]) + 0);
      *((unsigned short *)(& state[local1]) + 0) = copy11;
    }
    local1 ++;
  }
  output[0UL] = (state[0UL] & 690137161UL) ^ 1047729135U;
}
}