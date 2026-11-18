
int factors(int M, int* arr) {
 int i,N,num,mult,m1,m2;
 i = 0;
 N = M;
 while (N%53 == 0) {
  N = N/53;
  arr[i] = 53;
  i++;
 }
 while (N%47 == 0) {
  N = N/47;
  arr[i] = 47;
  i++;
 }
 while (N%43 == 0) {
  N = N/43;
  arr[i] = 43;
  i++;
 }
 while (N%41 == 0) {
  N = N/41;
  arr[i] = 41;
  i++;
 }
 while (N%37 == 0) {
  N = N/37;
  arr[i] = 37;
  i++;
 }
 while (N%31 == 0) {
  N = N/31;
  arr[i] = 31;
  i++;
 }
 while (N%29 == 0) {
  N = N/29;
  arr[i] = 29;
  i++;
 }
 while (N%23 == 0) {
  N = N/23;
  arr[i] = 23;
  i++;
 }
 while (N%19 == 0) {
  N = N/19;
  arr[i] = 19;
  i++;
 }
 while (N%17 == 0) {
  N = N/17;
  arr[i] = 17;
  i++;
 }
 while (N%13 == 0) {
  N = N/13;
  arr[i] = 13;
  i++;
 }
 while (N%11 == 0) {
  N = N/11;
  arr[i] = 11;
  i++;
 }
 while (N%8 == 0) {
  N = N/8;
  arr[i] = 8;
  i++;
 }
 while (N%7 == 0) {
  N = N/7;
  arr[i] = 7;
  i++;
 }
 while (N%5 == 0) {
  N = N/5;
  arr[i] = 5;
  i++;
 }
 while (N%4 == 0) {
  N = N/4;
  arr[i] = 4;
  i++;
 }
 while (N%3 == 0) {
  N = N/3;
  arr[i] = 3;
  i++;
 }
 while (N%2 == 0) {
  N = N/2;
  arr[i] = 2;
  i++;
 }
 if (N > 31) {
  num = 2;

  while (N > 1) {
   mult = num*6;
   m1 = mult-1;
   m2 = mult+1;
   while (N%m1 == 0 ) {
    arr[i] = m1;
    i++;
    N = N / m1;
   }
   while (N%m2 == 0 ) {
    arr[i] = m2;
    i++;
    N = N / m2;
   }
   num+=1;

  }
 }
 return i;

}
