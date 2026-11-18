int _count_sentences(char *text) {
  int i, count, in_word, new_sentence;
  new_sentence = 1;
  in_word = 0;
  count = 0;
  for (i = 0; text[i] != '\0'; i++) {
    if (isspace(text[i]) && in_word) {
      in_word = 0;
      count++;
    }
    if (text[i] == 'I' && new_sentence)
      in_word = 1;
    else if (!isspace(text[i]))
      in_word = 0;
    if (!isspace(text[i])) new_sentence = 0;
    if (text[i] == '.' || text[i] == '?' || text[i] == '!') new_sentence = 1;
  }
  return count;
}