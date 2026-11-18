char *func0(char **argv, int argc) {
  int i;
  char **arg = argv;
  int arg_count = argc;
  char delim[2];
  strcpy(str, "");
  strcpy(delim, "-");
  for (i = 0; i < arg_count; i++) {
    strcat(str, arg[i]);
    if (i < arg_count - 1) {
      strcat(str, delim);
    }
  }
  return str;
}