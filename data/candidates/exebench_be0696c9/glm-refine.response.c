float __cdecl get_near_num(float var, float *var_fix, float *var_fix_before)
{
  float ret_val; // [rsp+14h] [rbp-4h]

  if ( var_fix < var_fix_before )
  {
    *var_fix_before = *var_fix;
    return var;
  }
  return ret_val;
}