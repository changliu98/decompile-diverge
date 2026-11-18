int _is_valid_password(const char *password) {
  int has_alpha = 0;
  int has_digit = 0;
  for (; *password; password++) {
    if (isalpha((unsigned char)*password)) has_alpha = 1;
    if (isdigit((unsigned char)*password)) has_digit = 1;
  }
  return has_alpha && has_digit;
}