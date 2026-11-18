void func3(int i,int *j)

{
  int *j_local;
  int i_local;
  
  if (i < 1) {
    *j = *j + -1;
  }
  else {
    *j = *j + 1;
  }
  return;
}