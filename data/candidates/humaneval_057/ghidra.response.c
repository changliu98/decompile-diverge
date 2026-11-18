_Bool func0(float *l,int size)

{
  int i;
  int decr;
  int incr;
  int size_local;
  float *l_local;
  
  decr = 0;
  incr = 0;
  for (i = 1; i < size; i = i + 1) {
    if (l[i + -1] <= l[i] && l[i] != l[i + -1]) {
      incr = 1;
    }
    if (l[i] < l[i + -1]) {
      decr = 1;
    }
  }
  return incr + decr != 2;
}