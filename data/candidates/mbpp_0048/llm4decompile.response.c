int func0(int n)
{
 int i;
 int temp;
 int res;

 temp = n;
 res = 0;
 for (i = 0; temp > 0; i++) {
  if (i % 2 == 0) {
   res |= 1 << i;
  }
  temp = temp >> 1;
 }

 return res | n;
}