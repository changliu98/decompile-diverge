void func0(int *num_list,int size,int *result)

{
  int i_1;
  int i;
  int j;
  int zero_count;
  int *result_local;
  int size_local;
  int *num_list_local;
  
  zero_count = 0;
  j = 0;
  for (i = 0; i < size; i = i + 1) {
    if (num_list[i] == 0) {
      zero_count = zero_count + 1;
    }
    else {
      result[j] = num_list[i];
      j = j + 1;
    }
  }
  for (i_1 = 0; i_1 < zero_count; i_1 = i_1 + 1) {
    result[j] = 0;
    j = j + 1;
  }
  return;
}