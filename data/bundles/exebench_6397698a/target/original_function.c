char *truncate_string_at_char (char *str, char chr) {
  char *ptr = (char *) NULL;

  for (ptr = str; *ptr != '\0'; ptr++) {
    if (*ptr == chr) {
      *ptr = '\0';
    }
  }

  return str;
}