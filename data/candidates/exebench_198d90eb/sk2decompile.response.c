void advance_kpos(int *kpos) {
  kpos[0] = (kpos[0] + 1) % 41;
  kpos[1] = (kpos[1] + 1) % 31;
  kpos[2] = (kpos[2] + 1) % 29;
  kpos[3] = (kpos[3] + 1) % 26;
  kpos[4] = (kpos[4] + 1) % 23;
}