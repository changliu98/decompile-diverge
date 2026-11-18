int txq2vq(int txq)

{
  int txq_local;
  
  return txq * 2 + 1;
}