char * func0(int *lst1,int size1,int *lst2,int size2)

{
  int i_1;
  int i;
  int num;
  int size2_local;
  int *lst2_local;
  int size1_local;
  int *lst1_local;
  char *local_10;
  
  num = 0;
  for (i = 0; i < size1; i = i + 1) {
    if (lst1[i] % 2 == 0) {
      num = num + 1;
    }
  }
  for (i_1 = 0; i_1 < size2; i_1 = i_1 + 1) {
    if (lst2[i_1] % 2 == 0) {
      num = num + 1;
    }
  }
  if (num < size1) {
    local_10 = "NO";
  }
  else {
    local_10 = "YES";
  }
  return local_10;
}