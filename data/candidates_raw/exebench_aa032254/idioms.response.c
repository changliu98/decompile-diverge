void i8253_calc(int i8253_osc_base, int *div1, int *div2, int *nanosec, int round_mode)
{
  int base;
  int div2_max = 0x10000;
  int div1_max = 0x10000;
  int div2;
  for (div1 = 2; div1 <= div1_max; div1 *= 2)
  {
    base = i8253_osc_base * div1;
    round_mode &= 0x000000300000;
    switch (round_mode)
    {
      case 0:
      case 0x000000100000:
        div2 = (*nanosec + (base / 2)) / base;
        break;
      case 0x000000200000:
        div2 = (*nanosec + (base - 1)) / base;
        break;
    }
    if (div2 < 2)
      div2 = 2;
    if (div2 > div2_max)
      continue;
    *nanosec = base * div2;
    *div1 = div1 & 0xffff;
    *div2 = div2 & 0xffff;
    return;
  }
  *nanosec = 0;
  *div1 = 0;
  *div2 = 0;
}