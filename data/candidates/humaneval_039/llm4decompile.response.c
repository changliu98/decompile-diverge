int func0(int n) {
 int f1 = 1;
 int f2 = 2;
 int count = 0;
 while (count < n) {
  int tmp = f1 + f2;
  f1 = f2;
  f2 = tmp;
  int isprime = 1;
  for (int i = 2; i * i <= f2; i++) {
   if (f2 % i == 0) {
    isprime = 0;
    break;
   }
  }
  if (isprime) {
   count++;
  }
  if (count == n) {
   return f2;
  }
 }
 return 0;
}