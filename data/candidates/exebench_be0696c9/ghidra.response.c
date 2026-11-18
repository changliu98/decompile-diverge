float get_near_num(float var,float *var_fix,float *var_fix_before)

{
  float *var_fix_before_local;
  float *var_fix_local;
  float var_local;
  undefined4 local_c;
  
  if (var_fix < var_fix_before) {
    *var_fix_before = *var_fix;
    local_c = var;
  }
  return local_c;
}