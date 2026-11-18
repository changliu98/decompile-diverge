void MPI_Comm_rank(unsigned int input[1] , unsigned int output[1] )
{
  unsigned int state[1] ;
  unsigned int local2 ;
  unsigned int local1 ;
  unsigned short copy11 ;

  {
  output[0UL] = 0U;
  local1 = 0UL;
  while (local1 < 0U) {
    local2 = 0UL;
    while (local2 < 0U) {
      if (state[0UL] == local2) {
        copy11 = *((unsigned short *)(& state[local1]) + 0);
        *((unsigned short *)(& state[local1]) + 0) = *((unsigned short *)(& state[local1]) + 1);
        *((unsigned short *)(& state[local1]) + 1) = copy11;
      }
      local2 += 2UL;
    }
    local1 ++;
  }
}
}