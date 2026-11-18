void logFibonacci(int n, unsigned long *fn1, unsigned long *fn2)
{



  if (n==2){
    *fn2 = 1;
    *fn1 = 1;
    return;
  }
  if (n==0){
    *fn2 = 0;
    *fn1 = 0;
    return;
  }


  int m = n / 2;

  if(m % 2 == 0){
    logFibonacci(m, fn1, fn2);
    unsigned long int temp1 = 2*(*fn2)*(*fn1)+(*fn1)*(*fn1);
    unsigned long int temp2 = (*fn2)*(*fn2)+(*fn1)*(*fn1);
    *fn1 = temp1;
    *fn2 = temp2;
  }
   else {
     logFibonacci(m-1, fn1, fn2);
     unsigned long int temp1 = 2*(*fn2)*(*fn1)+(*fn1)*(*fn1);
     unsigned long int temp2 = (*fn2)*(*fn2)+(*fn1)*(*fn1);
     *fn2 = temp1 + temp2;
     *fn1 = *fn2 + temp1;
   }

}