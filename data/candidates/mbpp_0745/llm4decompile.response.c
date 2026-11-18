void func0(int startnum, int endnum, int *result, int *result_size)
{
 int i, j, temp, flag;
 *result_size = 0;

 for (i = startnum; i <= endnum; i++) {
  temp = i;
  flag = 1;
  while (temp > 0) {
   digit = temp % 10;
   if (digit == 0) {
    flag = 0;
    break;
   }
   if (i % digit != 0) {
    flag = 0;
    break;
   }
   temp = temp / 10;
  }
  if (flag) {
   result[*result_size] = i;
   *result_size = *result_size + 1;
  }
 }
}