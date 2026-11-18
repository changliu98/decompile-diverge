short goertzel_filter_v1(short *state, short sample, short coeff) {
  short s;
  s = (coeff * state[1]) >> 14;
  s -= state[2];
  s += (sample >> 7);
  state[2] = state[1];
  state[1] = s;
  return s;
}