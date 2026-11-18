void func0(int *num_list,int n,int *output)

{
  int iVar1;
  int i_2;
  int i_1;
  int i;
  int output_index;
  int count_first;
  int first_element;
  int *output_local;
  int n_local;
  int *num_list_local;
  
  iVar1 = *num_list;
  count_first = 0;
  output_index = 0;
  for (i = 0; i < n; i = i + 1) {
    if (num_list[i] == iVar1) {
      count_first = count_first + 1;
    }
  }
  for (i_1 = 0; i_1 < n; i_1 = i_1 + 1) {
    if (num_list[i_1] != iVar1) {
      output[output_index] = num_list[i_1];
      output_index = output_index + 1;
    }
  }
  for (i_2 = 0; i_2 < count_first; i_2 = i_2 + 1) {
    output[output_index] = iVar1;
    output_index = output_index + 1;
  }
  return;
}