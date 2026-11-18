void func0(int *num_list, int n, int *output){
  int first_element = num_list[0];
  int count_first = 0;
  int i;
  int output_index = 0;
  for (i = 0; i < n; i++) {
    if (num_list[i] == first_element) {
      count_first++;
    }
  }
  for (i = 0; i < n; i++) {
    if (num_list[i] != first_element) {
      output[output_index++] = num_list[i];
    }
  }
  for (i = 0; i < count_first; i++) {
    output[output_index++] = first_element;
  }
  return;
}