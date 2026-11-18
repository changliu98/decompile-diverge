int get_sorting_mode(int c)

{
  int c_local;
  int local_c;
  
  if ((c < 0) || (0x7f < c)) {
    local_c = -1;
  }
  else {
    local_c = tbl_sorting_mode[c];
  }
  return local_c;
}