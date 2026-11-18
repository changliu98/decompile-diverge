double estLog(double N){
  double logN, x;

  logN = 1;
  for(x=10; x<N; x*=10)
    logN += 1;

  return logN;
}