
int itoa(char *a, const int i) {
 if (i == 0) {
  *a = '0';
  *(a+1) = 0;
  return 2;
 }
 int charc = 0;
 int temp = 1;
 int abs_i = i < 0 ? -i : i;

 while (abs_i % temp != abs_i) {
  charc++;
  temp *= 10;
 }

 if (i < 0) {
  charc++;
 }

 int j;
 temp = 1;
 for (j = charc-1; j >= 0; j--) {
  *(a+j) = (((abs_i - (abs_i % temp)) / temp) % 10) + '0';
  temp *= 10;
 }
 if (i < 0) {
  *a = '-';
 }
 *(a+charc) = 0;

 return charc;
}
