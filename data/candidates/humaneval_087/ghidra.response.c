int ** func0(int **lst,int lst_size,int *row_sizes,int x,int *return_size)

{
  int **ppiVar1;
  int *piVar2;
  int j;
  int i;
  int count;
  int **out;
  int *return_size_local;
  int x_local;
  int *row_sizes_local;
  int lst_size_local;
  int **lst_local;
  
  ppiVar1 = malloc(800);
  count = 0;
  for (i = 0; i < lst_size; i = i + 1) {
    j = row_sizes[i];
    while (j = j + -1, -1 < j) {
      if (lst[i][j] == x) {
        piVar2 = malloc(8);
        ppiVar1[count] = piVar2;
        *ppiVar1[count] = i;
        ppiVar1[count][1] = j;
        count = count + 1;
      }
    }
  }
  *return_size = count;
  return ppiVar1;
}