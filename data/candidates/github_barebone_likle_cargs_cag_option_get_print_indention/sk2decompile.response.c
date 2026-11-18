static unsigned int cag_option_get_print_indention(
    cag_option_t *options, unsigned int option_count) {
  unsigned int indention = 20;
  for (unsigned int i = 0; i < option_count; i++) {
    unsigned int current_indention = 4;
    if (options[i].name && options[i].name[0]) {
      current_indention += strlen(options[i].name) * 4 - 2;
      if (options[i].description) {
        current_indention += 4 + strlen(options[i].description);
      }
    } else if (options[i].description) {
      current_indention += 6 + strlen(options[i].description);
    }
    if (options[i].value) {
      current_indention += 1 + strlen(options[i].value);
    }
    if (current_indention > indention) {
      indention = current_indention;
    }
  }
  return indention;
}