void intercambiar(int *pos1,int *pos2)

{
  int iVar1;
  int aux;
  int *pos2_local;
  int *pos1_local;
  
  if (pos1 != pos2) {
    iVar1 = *pos1;
    *pos1 = *pos2;
    *pos2 = iVar1;
  }
  return;
}