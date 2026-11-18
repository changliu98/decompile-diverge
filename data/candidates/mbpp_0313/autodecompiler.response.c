int func0(int *a, size_t n)
{
 int ret;
 int i = 0;

 while (1) {
  if (i < n) {
   if (a[i] >= 0) {
    ret = a[i];
    break;
   } else {
    i++;
   }
  } else {
   ret = -1;
   break;
  }
 }

 return ret;
}