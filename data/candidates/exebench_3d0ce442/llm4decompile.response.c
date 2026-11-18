float add_denormal_prevention_white_noise(uint32_t *rand_state)
{
   uint32_t r;
   uint32_t s;
   uint32_t t;

   s = *rand_state;
   t = 134217721;
   s = (s * t) + 8374611;
   *rand_state = s;
   r = s & 0x7f0000;
   r |= 0x1e000000;

   return *(float *)&r;
}