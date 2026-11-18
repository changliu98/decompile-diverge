void AdjustSpan(int *start,int *len,int max)

{
  int max_local;
  int *len_local;
  int *start_local;
  
  if (*start < 0) {
    *len = *start + *len;
    *start = 0;
  }
  if (max < *start + *len) {
    *len = max - *start;
  }
  return;
}