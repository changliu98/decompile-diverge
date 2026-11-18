void i8253_cascade_ns_to_timer_power
               (int i8253_osc_base,uint *d1,uint *d2,uint *nanosec,int round_mode)

{
  uint uVar1;
  int base;
  int div2;
  int div1;
  int round_mode_local;
  uint *nanosec_local;
  uint *d2_local;
  uint *d1_local;
  int i8253_osc_base_local;
  
  div1 = 2;
  round_mode_local = round_mode;
  do {
    if (0x10000 < div1) {
      *nanosec = 0;
      *d1 = 0;
      *d2 = 0;
      return;
    }
    uVar1 = i8253_osc_base * div1;
    round_mode_local = round_mode_local & 0x30000;
    if (round_mode_local == 0) {
LAB_00101680:
      div2 = (*nanosec + (int)uVar1 / 2) / uVar1;
    }
    else if (round_mode_local == 0x10000) {
      div2 = *nanosec / uVar1;
    }
    else {
      if (round_mode_local != 0x20000) goto LAB_00101680;
      div2 = ((*nanosec + uVar1) - 1) / uVar1;
    }
    if (div2 < 2) {
      div2 = 2;
    }
    if (div2 < 0x10001) {
      *nanosec = div2 * uVar1;
      *d1 = div1 & 0xffff;
      *d2 = div2 & 0xffff;
      return;
    }
    div1 = div1 << 1;
  } while( true );
}