char* func0(char** argv, int argc) {
  int i;
  strcpy(str, " ");
  for (i = 0; i < argc; i++) {
    strcat(str, " ");
    strcat(str, argv[i]);
  }
  return str;
}