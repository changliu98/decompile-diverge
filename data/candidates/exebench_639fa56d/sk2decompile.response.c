void advance_m2pos(int *m2pos) {
  *m2pos = *m2pos + 1;
  *m2pos = *m2pos % 37;
  return;
}