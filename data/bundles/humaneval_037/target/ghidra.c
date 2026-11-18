void func0(float *l,int size,float *out)

{
  float *pfVar1;
  float fVar2;
  undefined4 uVar3;
  void *__ptr;
  float temp;
  int even_count;
  int j;
  int i;
  float *even;
  float *out_local;
  int size_local;
  float *l_local;
  
  __ptr = malloc((long)(size / 2 + 1) << 2);
  even_count = 0;
  for (i = 0; i < size; i = i + 2) {
    *(float *)((long)__ptr + (long)even_count * 4) = l[i];
    even_count = even_count + 1;
  }
  for (i = 0; i < even_count + -1; i = i + 1) {
    for (j = 0; j < (even_count - i) + -1; j = j + 1) {
      fVar2 = *(float *)((long)__ptr + (long)j * 4);
      pfVar1 = (float *)((long)__ptr + (long)(j + 1) * 4);
      if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
        uVar3 = *(undefined4 *)((long)__ptr + (long)j * 4);
        *(undefined4 *)((long)__ptr + (long)j * 4) =
             *(undefined4 *)((long)__ptr + (long)(j + 1) * 4);
        *(undefined4 *)((long)__ptr + (long)(j + 1) * 4) = uVar3;
      }
    }
  }
  for (i = 0; i < size; i = i + 1) {
    if (i % 2 == 0) {
      out[i] = *(float *)((long)__ptr + (long)(i / 2) * 4);
    }
    else {
      out[i] = l[i];
    }
  }
  free(__ptr);
  return;
}