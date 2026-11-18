int meat_time_get_month_by_name(char *i_arg, unsigned long i_arg_len)
{
  int i_month = 0;
  char b_found = 0;
  if (i_arg_len == 3)
  {
    for ( ;
         (0 == b_found) && (i_month < 12);
         ++i_month )
    {
      if ( (i_arg[0] == meat_time_which_month_a_ref_month[i_month][0])
        && (i_arg[1] == meat_time_which_month_a_ref_month[i_month][1])
        && (i_arg[2] == meat_time_which_month_a_ref_month[i_month][2]) )
      {
        b_found = 1;
      }
    }
  }
  if (0 == b_found)
  {
    return -1;
  }
  return i_month;
}