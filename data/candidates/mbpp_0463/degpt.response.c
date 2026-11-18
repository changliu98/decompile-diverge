int func0(int *arr,int n)

{
  bool bVar1;
  int iVar2;
  int local_3c;
  int local_38;
  int temp;
  int i;
  int flag;
  int max_so_far;
  int min_ending_here;
  int max_ending_here;
  int n_local;
  int *arr_local;
  int local_c;
  
  max_ending_here = 1;
  min_ending_here = 1;
  max_so_far = 0;
  bVar1 = false;
  for (i = 0; iVar2 = max_ending_here, i < n; i = i + 1) {
    if (arr[i] < 1) {
      if (arr[i] == 0) {
        max_ending_here = 1;
        min_ending_here = 1;
      }
      else {
        if (min_ending_here * arr[i] < 2) {
          local_3c = 1;
        }
        else {
          local_3c = min_ending_here * arr[i];
        }
        max_ending_here = local_3c;
        min_ending_here = iVar2 * arr[i];
      }
    }
    else {
      max_ending_here = max_ending_here * arr[i];
      if (min_ending_here * arr[i] < 1) {
        local_38 = min_ending_here * arr[i];
      }
      else {
        local_38 = 1;
      }
      min_ending_here = local_38;
      bVar1 = true;
    }
    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
    }
  }
  if ((bVar1) || (max_so_far != 0)) {
    local_c = max_so_far;
  }
  else {
    local_c = 0;
  }
  return local_c;
}