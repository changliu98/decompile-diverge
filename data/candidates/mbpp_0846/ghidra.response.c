int func0(int *arr,int *dep,int n)

{
  int j;
  int i;
  int result;
  int plat_needed;
  int n_local;
  int *dep_local;
  int *arr_local;
  
  qsort(arr,(long)n,4,compare);
  qsort(dep,(long)n,4,compare);
  plat_needed = 1;
  result = 1;
  i = 1;
  j = 0;
  while (i < n && j < n) {
    if (dep[j] < arr[i]) {
      plat_needed = plat_needed + -1;
      j = j + 1;
    }
    else {
      plat_needed = plat_needed + 1;
      i = i + 1;
      if (result < plat_needed) {
        result = plat_needed;
      }
    }
  }
  return result;
}