void oct_to_word(char *word, unsigned char oct) {
  unsigned char i;
  if (word == NULL) return;
  word[0] = (oct & 0xC0) >> 6;
  word[1] = (oct & 0x38) >> 3;
  word[2] = oct & 0x07;
  for (i = 0; i < 3; i++) word[i] += 0x30;
}