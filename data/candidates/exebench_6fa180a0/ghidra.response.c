void sortVrtx(int *vrt)

{
  int iVar1;
  bool bVar2;
  int o;
  int tmp;
  int i;
  int *vrt_local;
  
  do {
    bVar2 = true;
    for (i = 1; i < 3; i = i + 1) {
      if (vrt[i] < vrt[i + -1]) {
        iVar1 = vrt[i];
        vrt[i] = vrt[i + -1];
        vrt[i + -1] = iVar1;
        bVar2 = false;
      }
    }
  } while (!bVar2);
  return;
}