void inc2(int *byref)

{
  int *byref_local;
  
  *byref = *byref + 1;
  return;
}