void multiply_all(int arr[10], int n) {
 int i = 0;
 while(1) {
  if (i >= 10) break;
  arr[i] *= n;
  i++;
 }
}