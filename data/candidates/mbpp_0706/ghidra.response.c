_Bool func0(int *arr1,int m,int *arr2,int n)

{
  int i_1;
  int i;
  _Bool hashset [1000];
  int n_local;
  int *arr2_local;
  int m_local;
  int *arr1_local;
  
  memset(hashset,0,1000);
  for (i = 0; i < m; i = i + 1) {
    hashset[arr1[i]] = true;
  }
  i_1 = 0;
  while( true ) {
    if (n <= i_1) {
      return true;
    }
    if ((hashset[arr2[i_1]] & 1U) == 0) break;
    i_1 = i_1 + 1;
  }
  return false;
}