void nist_increment_block(uint *V)

{
  uint32_t uVar1;
  uint32_t uVar2;
  uint x;
  int i;
  uint *V_local;
  
  i = 3;
  while( true ) {
    if (i < 0) {
      return;
    }
    uVar1 = ntohl(V[i]);
    uVar2 = htonl(uVar1 + 1);
    V[i] = uVar2;
    if (uVar1 + 1 != 0) break;
    i = i + -1;
  }
  return;
}