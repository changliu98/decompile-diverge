int meat_time_which_month(uchar *p_arg,size_t i_arg_len)

{
  bool bVar1;
  char b_found;
  int i_month;
  size_t i_arg_len_local;
  uchar *p_arg_local;
  
  i_month = 0;
  bVar1 = false;
  if (i_arg_len == 3) {
    while (!bVar1 && i_month < 0xc) {
      if ((((uint)*p_arg == (int)meat_time_which_month::a_ref_month[i_month][0]) &&
          ((uint)p_arg[1] == (int)meat_time_which_month::a_ref_month[i_month][1])) &&
         ((uint)p_arg[2] == (int)meat_time_which_month::a_ref_month[i_month][2])) {
        bVar1 = true;
      }
      else {
        i_month = i_month + 1;
      }
    }
  }
  if (!bVar1) {
    i_month = -1;
  }
  return i_month;
}