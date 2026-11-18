int __cdecl meat_time_which_month(const unsigned __int8 *const p_arg, const size_t i_arg_len)
{
  int i_month = 0;
  bool b_found = false;

  if (i_arg_len == 3)
  {
    while (!b_found && i_month < 12)
    {
      const char *ref_month = &meat_time_which_month_a_ref_month[3 * i_month];
      
      if (p_arg[0] == ref_month[0] && 
          p_arg[1] == ref_month[1] && 
          p_arg[2] == ref_month[2])
      {
        b_found = true;
      }
      else
      {
        ++i_month;
      }
    }
  }

  return b_found ? i_month : -1;
}