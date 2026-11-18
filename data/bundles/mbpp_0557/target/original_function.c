char* func0(char* string) {
  static char toggled_string[100];
  strcpy(toggled_string, string);
  for (int i = 0; toggled_string[i] != '\0'; i++) {
    if (isupper(toggled_string[i])) {
      toggled_string[i] = tolower(toggled_string[i]);
    } else if (islower(toggled_string[i])) {
      toggled_string[i] = toupper(toggled_string[i]);
    }
  }
  return toggled_string;
}