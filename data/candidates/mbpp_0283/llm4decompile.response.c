int func0(int n) {
 int i, count, temp;
 for (i = 0; i < 10; i++) {
  count = 0;
  temp = n;
  while (temp > 0) {
   if (temp % 10 == i)
    count++;
   if (count > i)
    return 0;
   temp /= 10;
  }
 }
 return 1;
}