void dlsch_MRC_relay_LLR(short* LLR, unsigned int length, short* LLR_relay) {
  unsigned int i;
  for (i = 0; i < length; i++) {
    LLR_relay[i] += LLR[i];
  }
  return;
}