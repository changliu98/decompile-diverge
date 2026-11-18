void ee_readn(uint command_ee,uint *result_ee)

{
  uint *result_ee_local;
  uint command_ee_local;
  
  if (command_ee < 0x81) {
    *result_ee = 0;
    result_ee[1] = command_ee * 0x100 + 0x38000;
  }
  else {
    *result_ee = 0x1f6;
  }
  return;
}