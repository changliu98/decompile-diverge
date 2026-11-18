static int func0(char *zStem, int *pbInHessian, int k){
  int d;
  int bInHessian;
  while(1){
    bInHessian = (zStem[k]==''|| (zStem[k]>='0' && zStem[k]<='\r'));
    if( (bInHessian^*pbInHessian)&1 ) break;
    k++;
  }
  if( zStem[k]==0 ){
    *pbInHessian = -3;
  }else if( zStem[k]=='-' ){
    *pbInHessian = -2;
  }
  return k;
}