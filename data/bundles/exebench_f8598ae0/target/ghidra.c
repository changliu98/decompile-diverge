int find(float xt,float *x,int n)

{
  int iVar1;
  int iVar2;
  int ihalf;
  int itst;
  int im;
  int il;
  int n_local;
  float *x_local;
  float xt_local;
  int local_c;
  
  if (*x < xt) {
    if (xt < x[n + -1]) {
      il = 1;
      itst = n + -1;
      im = n;
      while (1 < itst) {
        iVar2 = (im + il) / 2;
        iVar1 = iVar2;
        if (x[iVar2 + -1] <= xt) {
          iVar1 = im;
          il = iVar2;
        }
        im = iVar1;
        itst = im - il;
      }
      local_c = il + -1;
    }
    else {
      local_c = n + -1;
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}