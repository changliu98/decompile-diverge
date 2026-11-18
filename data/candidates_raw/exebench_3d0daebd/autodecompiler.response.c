void array_get_maxval_(double* x, int n, double *xmax){
  int i;
  *xmax = x[0];
  for(i=1;i<n;i++){
    if(x[i]>*xmax)
      *xmax = x[i];
  }
}