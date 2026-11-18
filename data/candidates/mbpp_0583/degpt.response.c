int func0(int num)

{
  int iVar1;
  int iVar2;
  int i;
  int res_num;
  int num_local;
  undefined4 local_c;
  
  if (num < 2) {
    local_c = 1;
  }
  else {
    res_num = 0;
    for (i = 0; i < num; i = i + 1) {
      iVar1 = func0(i);
      iVar2 = func0((num - i) + -1);
      res_num = iVar1 * iVar2 + res_num;
    }
    local_c = res_num;
  }
  return local_c;
}