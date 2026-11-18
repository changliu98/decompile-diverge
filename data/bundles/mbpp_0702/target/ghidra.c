int func0(int *arr,int n,int k)

{
  int iVar1;
  int local_28;
  int j;
  int i;
  int ans;
  int k_local;
  int n_local;
  int *arr_local;
  
  ans = n + -1;
  qsort(arr,(long)n,4,(__compar_fn_t)PTR_strcmp_00103fd8);
  for (i = 0; i < n; i = i + 1) {
    iVar1 = find_ind(arr[i],i,n,k,arr);
    if (iVar1 != -1) {
      if (ans < n - ((iVar1 - i) + 1)) {
        local_28 = ans;
      }
      else {
        local_28 = n - ((iVar1 - i) + 1);
      }
      ans = local_28;
    }
  }
  return ans;
}