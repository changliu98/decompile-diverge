void func0(char *sentence,char *out)

{
  bool bVar1;
  int j;
  int i;
  _Bool is_prime;
  int out_index;
  int word_len;
  int index;
  char *out_local;
  char *sentence_local;
  
  word_len = 0;
  out_index = 0;
  for (i = 0; sentence[i] != '\0'; i = i + 1) {
    if (sentence[i] == ' ') {
      if (word_len < 2) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
        for (j = 2; j * j <= word_len; j = j + 1) {
          if (word_len % j == 0) {
            bVar1 = false;
            break;
          }
        }
      }
      if (bVar1) {
        if (0 < out_index) {
          out[out_index] = ' ';
          out_index = out_index + 1;
        }
        memcpy(out + out_index,sentence + ((long)i - (long)word_len),(long)word_len);
        out_index = word_len + out_index;
      }
      word_len = 0;
    }
    else {
      word_len = word_len + 1;
    }
  }
  if (word_len < 2) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
    for (j = 2; j * j <= word_len; j = j + 1) {
      if (word_len % j == 0) {
        bVar1 = false;
        break;
      }
    }
  }
  if (bVar1) {
    if (0 < out_index) {
      out[out_index] = ' ';
      out_index = out_index + 1;
    }
    memcpy(out + out_index,sentence + ((long)i - (long)word_len),(long)word_len);
    out_index = word_len + out_index;
  }
  out[out_index] = '\0';
  return;
}