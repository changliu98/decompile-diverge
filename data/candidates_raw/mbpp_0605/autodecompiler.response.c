int is_prime(int n) {
 int i, j;
 char flag;

 if (n >= 2) {
  for (i = 2; ; ++i) {
   j = i;
   if (j <= n / 2) {
    if (n % i == 0) {
     flag = 0;
     break;
    }
   } else {
    flag = 1;
    break;
   }
  }
 } else {
  flag = 0;
 }

 return flag;
}