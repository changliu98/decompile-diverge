int func0(int n) {
 int arr[100] = {0};
 arr[1] = 0;
 arr[2] = 2;
 int i = 4;
 while (1) {
  if (i <= n) {
   arr[i] = arr[i-1] + arr[i-2] + arr[i-3] + arr[i-4];
   i++;
  } else {
   return arr[n];
  }
 }
}