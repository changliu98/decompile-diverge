int add(unsigned long long a, unsigned long long b, unsigned long long *sum)
{
 unsigned long long s, c;
 unsigned long long tmp;
 if(sum) {
  s = *sum;
 } else {
  s = &tmp;
 }
 c = a + b;
 *s = c;
 return ((c < a) && (c < b)) ? 1 : 0;
}