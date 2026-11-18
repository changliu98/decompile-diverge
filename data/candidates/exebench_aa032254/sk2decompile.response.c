static void i8253_cascade_ns_to_timer_power(unsigned int ns, unsigned int *div,
                                            unsigned int *count,
                                            unsigned int *rem,
                                            unsigned int rounding) {
  unsigned int d, c;
  for (d = 2; d <= 65536; d *= 2) {
    ns *= d;
    rounding &= 0x00030000;
    switch (rounding) {
      case 0x00000000:
        c = (*rem + ns / 2) / ns;
        break;
      case 0x00010000:
        c = (*rem + ns - 1) / ns;
        break;
      case 0x00020000:
        c = *rem / ns;
        break;
      default:
        c = (*rem + ns / 2) / ns;
        break;
    }
    if (c < 2) c = 2;
    if (c <= 65536) {
      *rem = c * ns;
      *div = d & 0xffff;
      *count = c & 0xffff;
      return;
    }
  }
  *rem = 0;
  *div = 0;
  *count = 0;
}