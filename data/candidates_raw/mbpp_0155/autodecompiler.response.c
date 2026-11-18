int comp(int num)
{
 int tmp = 0, cnt = 0, n = num;
 while (1) {
  if (n > 0) {
   if (cnt % 2 == 1)
    tmp |= (1 << cnt);
   cnt++;
   n >>= 1;
  } else
   return num ^ tmp;
 }
}