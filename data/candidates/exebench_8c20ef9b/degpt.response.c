void advance_spos(int *state_counters)
{
  // Increment the first state variable modulo 0x2b (43)
  *state_counters = (*state_counters + 1) % 0x2b;
  // Increment the second state variable modulo 0x2f (47)
  state_counters[1] = (state_counters[1] + 1) % 0x2f;
  // Increment the third state variable modulo 0x33 (51)
  state_counters[2] = (state_counters[2] + 1) % 0x33;
  // Increment the fourth state variable modulo 0x35 (53)
  state_counters[3] = (state_counters[3] + 1) % 0x35;
  // Increment the fifth state variable modulo 0x3b (59)
  state_counters[4] = (state_counters[4] + 1) % 0x3b;
}