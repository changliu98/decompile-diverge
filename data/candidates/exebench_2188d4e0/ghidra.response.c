void f(int *a,int *b)

{
  int *b_local;
  int *a_local;
  
  if (*b < *a) {
    *a = *a / 2;
    *b = *b << 1;
  }
  else {
    *a = *a << 1;
    *b = *b / 2;
  }
  return;
}