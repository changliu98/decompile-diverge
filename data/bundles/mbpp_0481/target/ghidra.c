_Bool func0(int *set,int n,int sum)

{
  _Bool _Var1;
  _Bool local_21;
  int sum_local;
  int n_local;
  int *set_local;
  _Bool local_9;
  
  if (sum == 0) {
    local_9 = true;
  }
  else if (n == 0) {
    local_9 = false;
  }
  else if (sum < set[n + -1]) {
    local_9 = func0(set,n + -1,sum);
  }
  else {
    _Var1 = func0(set,n + -1,sum);
    local_21 = true;
    if (!_Var1) {
      local_21 = func0(set,n + -1,sum - set[n + -1]);
    }
    local_9 = local_21;
  }
  return local_9;
}