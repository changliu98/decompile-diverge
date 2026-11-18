void next(int *i,int *j,int p)

{
  int p_local;
  int *j_local;
  int *i_local;
  
  *j = *j + 1;
  if (*j == p) {
    *j = 0;
    *i = *i + 1;
  }
  return;
}