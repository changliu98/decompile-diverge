int sum(int *data, int n)
{
  int total = 0;
  int i;
  for (i = 0; i < n; i++) {
    if (data[i] < 0) {
      int sub_length = -data[i];
      int j = i + 1;
      total += sum(&data[j], sub_length);
      i = j + sub_length - 1;
    }
    else {
      total += data[i];
    }
  }
  return total;
}