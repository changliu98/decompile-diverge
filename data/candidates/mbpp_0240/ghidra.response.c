void func0(int *list1,int list1_size,int *list2,int list2_size,int *result)

{
  int j;
  int i;
  int *result_local;
  int list2_size_local;
  int *list2_local;
  int list1_size_local;
  int *list1_local;
  
  for (i = 0; i < list1_size + -1; i = i + 1) {
    result[i] = list1[i];
  }
  for (j = 0; j < list2_size; j = j + 1) {
    result[list1_size + -1 + j] = list2[j];
  }
  return;
}