/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong func0(float *lst,int lst_size)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int i;
  longlong sum;
  int lst_size_local;
  float *lst_local;
  
  sum = 0;
  for (i = 0; i < lst_size; i = i + 1) {
    fVar1 = lst[i];
    dVar2 = round((double)lst[i]);
    if ((((double)((ulong)((double)fVar1 - dVar2) & _DAT_00102010) < DAT_00102008) && (0.0 < lst[i])
        ) && (dVar2 = round((double)lst[i]), (int)dVar2 % 2 == 1)) {
      dVar2 = round((double)lst[i]);
      dVar3 = round((double)lst[i]);
      sum = (int)dVar2 * (int)dVar3 + sum;
    }
  }
  return sum;
}