static float add_denormal_prevention_white_noise(unsigned int *seed) {
  *seed = *seed * 1234567 + 890123;
  float white_noise = *seed & 0x700000 | 0x18000000;
  return white_noise;
}