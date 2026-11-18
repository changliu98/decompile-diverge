void max1D_double(double* input,int len,double* retVals){







  int i;
  retVals[0]=-1;
  retVals[1]=-1e20;
  for(i=0;i<len;i++){
    if(input[i]>retVals[1]){
      retVals[1]=input[i];
      retVals[0]=i;
    }
  }
}