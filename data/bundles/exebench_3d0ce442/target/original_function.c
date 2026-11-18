float add_denormal_prevention_white_noise(unsigned int *rand_state)
{
 *rand_state = *rand_state * 1234567UL + 890123UL;
 int mantissa = *rand_state & 0x007F0000;
 int flt_rnd = mantissa | 0x1E000000;
 return *((float*)(&flt_rnd));
}