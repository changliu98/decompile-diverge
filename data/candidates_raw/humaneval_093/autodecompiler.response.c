void iglatinpay(char engin[], char pigin[]) {
  int i, j;
  char *vowels = "aeiouAEIOU";
  char ch;

  for (i = 0;; i++) {
    if (engin[i] == '\0') {
      pigin[i] = '\0';
      break;
    }
    ch = engin[i];

    if (((*___ctype_b_loc ())[(int) ((ch))] & (unsigned short int) 512))
      ch = toupper(ch);
    else if (((*___ctype_b_loc ())[(int) ((ch))] & (unsigned short int) 256))
      ch = tolower(ch);

    for (j = 0; vowels[j] != '\0'; j++)
      if (ch == vowels[j]) {
        if (j < 11)
          ch += 2;
        break;
      }

    pigin[i] = ch;
  }
}