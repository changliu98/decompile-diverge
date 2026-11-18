void func0(int* input_list, int list_size, int n, int* output_list,
           int* output_size) {
  int j = 0;
  for (int i = 0; i < list_size; i += n) {
    output_list[j++] = input_list[i];
  }
  *output_size = j;
}