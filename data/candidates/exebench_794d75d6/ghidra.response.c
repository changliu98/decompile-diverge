void AdjustSpan2(int *start,int *u,int *len,int max)

{
  int max_local;
  int *len_local;
  int *u_local;
  int *start_local;
  
  if (*start < 0) {
    *len = *start + *len;
    *u = *u - *start;
    *start = 0;
  }
  if (max < *start + *len) {
    *len = max - *start;
  }
  return;
}