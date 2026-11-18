int func0(int num) {
 int i, result = 18;

 if(num < 2) {
  result = 0;
 } else if(num == 1) {
  result = 1;
 } else {
  for(i=2; i<num; ) {
   result *= 10;
   i++;
  }
 }

 return result;
}