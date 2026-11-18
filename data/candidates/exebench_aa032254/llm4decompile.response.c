void i8253_cascade_ns_to_timer_power(
 int i8253_osc_base, int *power1, int *power2, int *nanosec, int round_mode)
{
 int i;
 int divisor1;
 int divisor2;
 int best_divisor1;
 int best_divisor2;
 int best_error;
 int error;
 int target;
 int current_rate;







 divisor1 = 2;
 best_divisor1 = 0;
 best_divisor2 = 0;
 best_error = 0;
 target = *nanosec;
 while (divisor1 <= 65536) {
  current_rate = i8253_osc_base * divisor1;
  round_mode &= 0x30000;
  if (round_mode == 0x00000) {
   divisor2 = (target + current_rate / 2) / current_rate;
  } else if (round_mode == 0x10000) {
   divisor2 = target / current_rate;
  } else if (round_mode == 0x20000) {
   divisor2 = (target + current_rate - 1) / current_rate;
  } else {
   divisor2 = (target + current_rate / 2) / current_rate;
  }
  if (divisor2 < 2) {
   divisor2 = 2;
  }
  if (divisor2 > 65536) {
   divisor1 *= 2;
   continue;
  }
  error = abs(target - divisor2 * current_rate);
  if ((best_error == 0) || (error < best_error)) {
   best_divisor1 = divisor1;
   best_divisor2 = divisor2;
   best_error = error;
  }
  divisor1 *= 2;
 }
 if (best_divisor1 == 0) {
  *nanosec = 0;
  *power1 = 0;
  *power2 = 0;
 } else {
  *nanosec = best_divisor2 * i8253_osc_base * best_divisor1;
  *power1 = best_divisor1;
  *power2 = best_divisor2;
 }
}