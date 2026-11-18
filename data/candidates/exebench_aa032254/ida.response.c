void __cdecl i8253_cascade_ns_to_timer_power(
        int i8253_osc_base,
        unsigned int *d1,
        unsigned int *d2,
        unsigned int *nanosec,
        int round_mode)
{
  unsigned int base; // [rsp+8h] [rbp-30h]
  int div2; // [rsp+Ch] [rbp-2Ch]
  int div1; // [rsp+10h] [rbp-28h]

  for ( div1 = 2; div1 <= 0x10000; div1 *= 2 )
  {
    base = div1 * i8253_osc_base;
    round_mode &= 0x30000u;
    switch ( round_mode )
    {
      case 0:
        goto LABEL_6;
      case 0x10000:
        div2 = *nanosec / base;
        break;
      case 0x20000:
        div2 = (base + *nanosec - 1) / base;
        break;
      default:
LABEL_6:
        div2 = ((int)base / 2 + *nanosec) / base;
        break;
    }
    if ( div2 < 2 )
      div2 = 2;
    if ( div2 <= 0x10000 )
    {
      *nanosec = base * div2;
      *d1 = (unsigned __int16)div1;
      *d2 = (unsigned __int16)div2;
      return;
    }
  }
  *nanosec = 0;
  *d1 = 0;
  *d2 = 0;
}