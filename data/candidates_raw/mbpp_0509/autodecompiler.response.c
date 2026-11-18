int fibSumEven(int n) {
 if (n % 2 == 0) {
  printf("Invalid Input\n");
  int err = -1;
  return err;
 }
 int sum = 0;
 int num = 0;
 while (n > 1) {
  num++;
  sum += n;
  n = n-2;
 }
 int ans = sum/num;
 return ans;
}