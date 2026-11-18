int sumEven(int *A, int size){
 int i;
 int sum = 0;

 for(i=0; ; i++){
  if(2*i+1 >= size)
   break;
  if(A[2*i+1] % 2 == 0)
   sum += A[2*i+1];
 }

 return sum;
}