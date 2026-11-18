void hex_to_word(char *word, char hex) {
  char i;
  if (word == NULL) return;
  word[0] = (hex & 0xF0) >> 4;
  word[1] = hex & 0x0F;
  for (i = 0; i < 2; i++) {
    if (word[i] > 9)
      word[i] += 55;
    else
      word[i] += 48;
  }
}