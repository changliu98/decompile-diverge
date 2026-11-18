void adjust_mode_num(int *mode)

{
  int *mode_local;
  
  if (*mode < 10) {
    if (*mode < 0) {
      *mode = 0;
    }
  }
  else {
    *mode = 9;
  }
  return;
}