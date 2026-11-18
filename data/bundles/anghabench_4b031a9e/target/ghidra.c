int valid_bo_pre_v2(long value)

{
  long value_local;
  undefined4 local_c;
  
  if ((value & 0x14U) == 0) {
    local_c = 1;
  }
  else if ((value & 0x14U) == 4) {
    local_c = (uint)((value & 2U) == 0);
  }
  else if ((value & 0x14U) == 0x10) {
    local_c = (uint)((value & 8U) == 0);
  }
  else {
    local_c = (uint)(value == 0x14);
  }
  return local_c;
}