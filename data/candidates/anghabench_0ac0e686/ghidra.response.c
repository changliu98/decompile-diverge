int int_to_ibta_mtu(int mtu)

{
  int mtu_local;
  undefined4 local_c;
  
  if (mtu == 0x100) {
    local_c = IB_MTU_256;
  }
  else if (mtu == 0x200) {
    local_c = IB_MTU_512;
  }
  else if (mtu == 0x400) {
    local_c = IB_MTU_1024;
  }
  else if (mtu == 0x800) {
    local_c = IB_MTU_2048;
  }
  else if (mtu == 0x1000) {
    local_c = IB_MTU_4096;
  }
  else {
    local_c = -1;
  }
  return local_c;
}