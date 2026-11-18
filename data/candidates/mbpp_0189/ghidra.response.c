int func0(int *arr,int n)

{
  bool bVar1;
  int iVar2;
  int i_3;
  int i_2;
  int i_1;
  int i;
  int ptr;
  int n_local;
  int *arr_local;
  int local_c;
  
  bVar1 = false;
  i = 0;
  do {
    if (n <= i) {
LAB_00101216:
      if (bVar1) {
        for (i_1 = 0; i_1 < n; i_1 = i_1 + 1) {
          if ((arr[i_1] < 1) || (n < arr[i_1])) {
            arr[i_1] = 1;
          }
        }
        for (i_2 = 0; i_2 < n; i_2 = i_2 + 1) {
          iVar2 = (arr[i_2] + -1) % n;
          arr[iVar2] = n + arr[iVar2];
        }
        for (i_3 = 0; i_3 < n; i_3 = i_3 + 1) {
          if (arr[i_3] <= n) {
            return i_3 + 1;
          }
        }
        local_c = n + 1;
      }
      else {
        local_c = 1;
      }
      return local_c;
    }
    if (arr[i] == 1) {
      bVar1 = true;
      goto LAB_00101216;
    }
    i = i + 1;
  } while( true );
}