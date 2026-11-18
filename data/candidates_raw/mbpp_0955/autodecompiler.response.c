int abundant(int n){
 int sum = 0;
 int i = 1;
 while(1){
  if(i >= n) break;
  if(n%i == 0){
   sum += i;
  }
  i++;
 }
 return sum > n;
}