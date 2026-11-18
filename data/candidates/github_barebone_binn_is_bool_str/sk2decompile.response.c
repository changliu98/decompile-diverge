int is_bool_str(const char *str, int *val) {
  if (!str || !val) return 0;
  if (!strcasecmp(str, "true") || !strcasecmp(str, "yes") ||
      !strcasecmp(str, "on")) {
    *val = 1;
    return 1;
  }
  if (!strcasecmp(str, "false") || !strcasecmp(str, "no") ||
      !strcasecmp(str, "off")) {
    *val = 0;
    return 1;
  }
  if (is_integer(str)) {
    *val = atoi64(str) != 0;
    return 1;
  }
  if (is_float(str)) {
    *val = atof(str) != 0.0;
    return 1;
  }
  return 0;
}