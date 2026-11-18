const char* func0(const char* string) {
  char vowels[] = "AEIOUaeiou";
  int count = 0;
  int found[10] = {0};
  for (int i = 0; string[i] != '\0'; i++) {
    for (int j = 0; j < 10; j++) {
      if (string[i] == vowels[j] && found[j] == 0) {
        found[j] = 1;
        count++;
        break;
      }
    }
  }
  if (count >= 5) {
    return "accepted";
  } else {
    return "not accepted";
  }
}