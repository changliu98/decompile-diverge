bool _is_valid_password(const char *password) {
  int length = strlen(password);
  bool has_lower = false;
  bool has_upper = false;
  bool has_digit = false;
  bool has_special = false;
  if (length < 6 || length > 12) {
    return false;
  }
  for (int i = 0; i < length; i++) {
    if (islower(password[i])) {
      has_lower = true;
    } else if (isupper(password[i])) {
      has_upper = true;
    } else if (isdigit(password[i])) {
      has_digit = true;
    } else if (password[i] == '$' || password[i] == '#' || password[i] == '@') {
      has_special = true;
    } else if (isspace(password[i])) {
      return false;
    }
  }
  return has_lower && has_upper && has_digit && has_special;
}