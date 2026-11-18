void func0(int *input_list,int list_size,int n,int *output_list,int *output_size)

{
  int i;
  int j;
  int *output_size_local;
  int *output_list_local;
  int n_local;
  int list_size_local;
  int *input_list_local;
  
  j = 0;
  for (i = 0; i < list_size; i = n + i) {
    output_list[j] = input_list[i];
    j = j + 1;
  }
  *output_size = j;
  return;
}