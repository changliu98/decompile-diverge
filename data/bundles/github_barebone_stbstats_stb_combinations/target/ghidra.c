int stb_combinations(int n,int t,int ***combinations)

{
  int iVar1;
  int rowsize;
  int *c_00;
  double dVar2;
  double dVar3;
  double dVar4;
  int x;
  int j;
  int nCr;
  int current;
  int *c;
  int **comb;
  int ***combinations_local;
  int t_local;
  int n_local;
  
  combinations_local = combinations;
  t_local = t;
  n_local = n;
  c_00 = calloc((long)(t + 3),4);
  current = 0;
  dVar2 = stb_factorial(n_local);
  dVar3 = stb_factorial(t_local);
  dVar4 = stb_factorial(n_local - t_local);
  rowsize = (int)(dVar2 / (dVar3 * dVar4));
  comb = stb_allocmat(rowsize,t_local,4);
  for (j = 1; j <= t_local; j = j + 1) {
    c_00[j] = j + -1;
  }
  c_00[t_local + 1] = n_local;
  c_00[t_local + 2] = 0;
  j = t_local;
  while( true ) {
    stb_visit(c_00,t_local,&comb,current);
    while (current = current + 1, 0 < j) {
      c_00[j] = j;
      j = j + -1;
      stb_visit(c_00,t_local,&comb,current);
    }
    while (c_00[1] + 1 < c_00[2]) {
      c_00[1] = c_00[1] + 1;
      stb_visit(c_00,t_local,&comb,current);
      while (current = current + 1, 0 < j) {
        c_00[j] = j;
        j = j + -1;
        stb_visit(c_00,t_local,&comb,current);
      }
    }
    j = 2;
    c_00[1] = 0;
    iVar1 = c_00[2];
    while (x = iVar1 + 1, x == c_00[j + 1]) {
      c_00[j] = j + -1;
      iVar1 = c_00[j + 1];
      j = j + 1;
    }
    if (t_local < j) break;
    c_00[j] = x;
    j = j + -1;
  }
  *combinations_local = comb;
  free(c_00);
  return rowsize;
}