float * func0(float *l,int count,int *out_count)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  int i;
  float *out;
  int *out_count_local;
  int count_local;
  float *l_local;
  
  pfVar3 = malloc((long)count << 2);
  *out_count = 0;
  for (i = 0; i < count; i = i + 1) {
    if (0.0 < l[i]) {
      fVar1 = l[i];
      iVar2 = *out_count;
      *out_count = iVar2 + 1;
      pfVar3[iVar2] = fVar1;
    }
  }
  return pfVar3;
}