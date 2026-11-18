unsigned long do_csum(void *buff, int len, int sum)
{
 unsigned long result = sum;







 if ((intptr_t)buff & 2) {
  result += *(uint16_t *)buff;
  buff = (void *)((intptr_t)buff + 2);
 }







 return result;
}