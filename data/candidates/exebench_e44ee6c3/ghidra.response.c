int compare(int *min,int *mid,int *max)

{
  int iVar1;
  int temp;
  int *max_local;
  int *mid_local;
  int *min_local;
  
  if (*mid < *min) {
    iVar1 = *min;
    *min = *mid;
    *mid = iVar1;
  }
  if (*max < *min) {
    iVar1 = *min;
    *min = *max;
    *max = iVar1;
  }
  if (*max < *mid) {
    iVar1 = *mid;
    *mid = *max;
    *max = iVar1;
  }
  return 0;
}