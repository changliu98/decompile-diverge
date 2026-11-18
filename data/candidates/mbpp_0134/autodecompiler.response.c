char * func0(int *prices, int size, int flag){
 int sum = 0;
 int i;
 for(i = 0; ;){
  if(i >= size){
   break;
  }
  sum += prices[i];
  i++;
 }

 char * res;
 if(flag == 1){
  if(sum % 2 == 0){
   res = "ODD";
  }else{
   res = "EVEN";
  }
 }else{
  res = "EVEN";
 }
 return res;
}