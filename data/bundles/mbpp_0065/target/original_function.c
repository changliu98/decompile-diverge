int func0(int *data_list, int n) {
  int total = 0;
  for (int i = 0; i < n; i++) {
    if (data_list[i] < 0) {
      int sub_length = -data_list[i];
      i++;
      total += func0(&data_list[i], sub_length);
      i += sub_length - 1;
    } else {
      total += data_list[i];
    }
  }
  return total;
}