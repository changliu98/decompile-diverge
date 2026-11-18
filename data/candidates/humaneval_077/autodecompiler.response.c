int func0(int n)
{
 int i = 0, j, k;
 while (1) {
  j = i * i * i;
  if (j <= abs(n)) {
   k = i * i * i;
   if (k == abs(n)) {
    return 1;
   }
  } else {
   break;
  }
  i++;
 }
 return 0;
}