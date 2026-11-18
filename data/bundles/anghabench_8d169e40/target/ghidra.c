uchar fsp_test_invert_cmd(uchar reg_val)

{
  uchar reg_val_local;
  byte local_9;
  
  if ((((reg_val == 0xe9) || (reg_val == 0xee)) || (reg_val == 0xf2)) ||
     (local_9 = reg_val, reg_val == 0xff)) {
    local_9 = reg_val ^ 0xff;
  }
  return local_9;
}