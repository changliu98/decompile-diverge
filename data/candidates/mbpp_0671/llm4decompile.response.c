int func0(int n)
{
 int result;

 if (n == 0) {
  result = 1;
 } else {
  if (n & (n + 1)) {
   result = n | (1 << ((int)(log2((double)(n ^ -n)) + 0.5) - 1));
  } else {
   result = n;
  }
 }

 return result;
}