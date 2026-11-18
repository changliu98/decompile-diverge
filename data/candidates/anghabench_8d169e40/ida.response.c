unsigned __int8 __cdecl fsp_test_invert_cmd(unsigned __int8 reg_val)
{
  if ( reg_val == 233 || reg_val == 238 || reg_val == 242 || reg_val == 255 )
    return ~reg_val;
  else
    return reg_val;
}