_Bool func0(int A,int B)

{
  int B_local;
  int A_local;
  _Bool local_9;
  
  B_local = B;
  for (A_local = A; 0 < A_local && 0 < B_local; A_local = A_local / 10) {
    B_local = B_local / 10;
  }
  if ((A_local == 0) && (B_local == 0)) {
    local_9 = true;
  }
  else {
    local_9 = false;
  }
  return local_9;
}