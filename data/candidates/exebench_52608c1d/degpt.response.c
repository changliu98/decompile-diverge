void MatrixM(int *a,int *b)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int t4;
  int t3;
  int t2;
  int t1;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  iVar2 = b[1];
  iVar3 = b[3];
  iVar4 = *b;
  iVar5 = b[2];
  iVar6 = a[2];
  iVar7 = b[1];
  iVar8 = b[3];
  *a = (*a * *b + a[1] * b[2]) % 100;
  a[1] = (iVar1 * iVar2 + a[1] * iVar3) % 100;
  a[2] = (a[2] * iVar4 + a[3] * iVar5) % 100;
  a[3] = (iVar6 * iVar7 + a[3] * iVar8) % 100;
  return;
}