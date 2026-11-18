int func0(int *A,int N)

{
  int j;
  int i;
  int evenPair;
  int N_local;
  int *A_local;
  
  evenPair = 0;
  for (i = 0; j = i, i < N; i = i + 1) {
    while (j = j + 1, j < N) {
      if ((A[i] ^ A[j]) % 2 == 0) {
        evenPair = evenPair + 1;
      }
    }
  }
  return evenPair;
}