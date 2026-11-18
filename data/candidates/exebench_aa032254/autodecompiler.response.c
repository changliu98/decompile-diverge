void
i8253_cascade_ns_to_timer_power(int osc, int *divisor1, int *divisor2,
     unsigned long *period, int round_mode)
{
 int divisor1a, divisor2a;
 int divisor1b, divisor2b;
 int divisor1c, divisor2c;
 int divisor1d, divisor2d;

 divisor1b = 2;
 for (;;) {
  if (divisor1b > 0x10000) {
   divisor1b = 0x10000;
   divisor2b = 0x10000;
   break;
  }
  divisor1a = osc * divisor1b;
  switch (round_mode & (0x010000 | 0x020000)) {
  case 0x010000:
   divisor2a = (*period + divisor1a / 2) / divisor1a;
   break;
  case 0x020000:
   divisor2a = *period / divisor1a;
   break;
  case 0x010000 | 0x020000:
   divisor2a = (*period + divisor1a - 1) / divisor1a;
   break;
  default:
   divisor2a = *period / divisor1a;
   break;
  }
  if (divisor2a < 2)
   divisor2a = 2;
  if (divisor2a <= 0x10000) {
   divisor2b = divisor2a;
   break;
  }
  divisor1b <<= 1;
 }

 divisor1c = divisor1b;
 divisor2c = divisor2b;
 divisor1d = divisor1b;
 divisor2d = divisor2b;
 *period = divisor1d * divisor2d * osc;
 *divisor1 = divisor1d & 0xffff;
 *divisor2 = divisor2d & 0xffff;
}