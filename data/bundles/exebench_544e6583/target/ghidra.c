void SWAP(int *a,int *b)

{
  int *b_local;
  int *a_local;
  
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
  return;
}