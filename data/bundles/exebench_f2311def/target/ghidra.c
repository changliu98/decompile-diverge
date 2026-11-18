int INDMAXVAL(float *val,int i1,int i2)

{
  int ini;
  int i;
  int i2_local;
  int i1_local;
  float *val_local;
  
  ini = i1;
  while (i = i1 + 1, i <= i2) {
    i1 = i;
    if (val[ini] < val[i]) {
      ini = i;
    }
  }
  return ini;
}