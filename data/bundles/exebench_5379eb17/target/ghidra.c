void max_ptr(int *p,int *q)

{
  int *q_local;
  int *p_local;
  
  if (*q < *p) {
    *p = *p ^ *q;
    *q = *p ^ *q;
    *p = *p ^ *q;
  }
  return;
}