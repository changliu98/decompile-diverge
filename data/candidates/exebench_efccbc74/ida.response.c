int __cdecl meat_time_which_month(const unsigned __int8 *const p_arg, const size_t i_arg_len)
{
  bool v3; // [rsp+0h] [rbp-16h]
  char b_found; // [rsp+1h] [rbp-15h]
  int i_month; // [rsp+2h] [rbp-14h]

  i_month = 0;
  b_found = 0;
  if ( i_arg_len == 3 )
  {
    while ( 1 )
    {
      v3 = 0;
      if ( !b_found )
        v3 = i_month < 12;
      if ( !v3 )
        break;
      if ( *p_arg == meat_time_which_month_a_ref_month[3 * i_month]
        && p_arg[1] == meat_time_which_month_a_ref_month[3 * i_month + 1]
        && p_arg[2] == meat_time_which_month_a_ref_month[3 * i_month + 2] )
      {
        b_found = 1;
      }
      else
      {
        ++i_month;
      }
    }
  }
  if ( !b_found )
    return -1;
  return i_month;
}