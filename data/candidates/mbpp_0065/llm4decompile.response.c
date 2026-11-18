int func0(int *data_list, int n) {
 int total = 0;
 int i = 0;
 while (i < n) {
  if (data_list[i] >= 0) {
   total += data_list[i];
   i++;
  } else {
   int sub_length = -data_list[i];
   total += func0(data_list + i + 1, sub_length);
   i += sub_length + 1;
  }
 }
 return total;
}