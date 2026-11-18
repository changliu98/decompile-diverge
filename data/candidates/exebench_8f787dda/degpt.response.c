void index_to_xwy(int index,int width,int *x,int *y)

{
  int *y_local;
  int *x_local;
  int width_local;
  int index_local;
  
  *x = index % width;
  *y = index / width;
  return;
}