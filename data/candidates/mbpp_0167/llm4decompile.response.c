int func0(int n)
{
 int count = 0;
 int result = 0;

 if (n != 0 && (n & (n - 1)) == 0) {
  result = n;
 } else {
  while (n != 0) {
   count++;
   n >>= 1;
  }

  result = 1 << count;
 }

 return result;
}