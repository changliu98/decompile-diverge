char **_parse_string(const char *str, int *argc) {
  int max_args = 10;
  char **args = malloc(max_args * sizeof(char *));
  char *arg = malloc(strlen(str) + 1);
  int num_args = 0;
  int arg_len = 0;
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ' || str[i] == ',') {
      if (arg_len > 0) {
        arg[arg_len] = '\0';
        args[num_args++] = strdup(arg);
        arg_len = 0;
        if (num_args >= max_args) {
          max_args *= 2;
          args = realloc(args, max_args * sizeof(char *));
        }
      }
    } else {
      arg[arg_len++] = str[i];
    }
  }
  if (arg_len > 0) {
    arg[arg_len] = '\0';
    args[num_args++] = strdup(arg);
  }
  free(arg);
  *argc = num_args;
  return args;
}