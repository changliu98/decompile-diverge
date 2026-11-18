float func0(int *arr1,int *arr2,int n)

{
  int iVar1;
  int count;
  int m2;
  int m1;
  int j;
  int i;
  int n_local;
  int *arr2_local;
  int *arr1_local;
  
  i = 0;
  j = 0;
  m1 = -1;
  m2 = -1;
  count = 0;
  do {
    iVar1 = m2;
    if (n + 1 <= count) {
LAB_001012d1:
      return (float)((double)(m1 + m2) / DAT_00102008);
    }
    count = count + 1;
    if (i == n) {
      m1 = m2;
      m2 = *arr2;
      goto LAB_001012d1;
    }
    if (j == n) {
      m1 = m2;
      m2 = *arr1;
      goto LAB_001012d1;
    }
    if (arr2[j] < arr1[i]) {
      m2 = arr2[j];
      j = j + 1;
    }
    else {
      m2 = arr1[i];
      i = i + 1;
    }
    m1 = iVar1;
  } while( true );
}