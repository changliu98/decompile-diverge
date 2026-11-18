void chartobit(int n, char* buffer) {
 int i = 8 - 1;
 while (1) {
  if (i > 0) {
   buffer[i] = ((n % 2) == 1 ? '1' : '0');
   n = n / 2;
   i--;
  } else {
   buffer[0] = ((n % 2) == 1 ? '1' : '0');
   return;
  }
 }
}