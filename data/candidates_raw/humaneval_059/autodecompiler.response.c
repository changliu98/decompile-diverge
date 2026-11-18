int Lpf(int num) {
 int lpf = 2;

 while (lpf * lpf <= num) {
  while ((num % lpf == 0) && (num > lpf)) {
   num /= lpf;
  }
  lpf++;
 }

 return num;
}