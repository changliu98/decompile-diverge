char *func0(const char *str1) {
  static char result[200];
  int has_upper = 0, has_lower = 0, has_digit = 0, is_valid = 1;
  int length = strlen(str1);
  for (int i = 0; i < length; i++) {
    if (isupper(str1[i])) {
      has_upper = 1;
    }
    if (islower(str1[i])) {
      has_lower = 1;
    }
    if (isdigit(str1[i])) {
      has_digit = 1;
    }
  }
  result[0] = '\0';
  if (!has_upper) {
    strcat(result, "String must have 1 upper case character,");
  }
  if (!has_lower) {
    strcat(result, "String must have 1 lower case character,");
  }
  if (!has_digit) {
    strcat(result, "String must have 1 number,");
  }
  if (length < 8) {
    strcat(result, "String length should be atleast 8,");
  }
  if (has_upper && has_lower && has_digit && length >= 8) {
    strcpy(result, "Valid string.");
  } else {
    int lastIdx = strlen(result) - 1;
    if (result[lastIdx] == ',') {
      result[lastIdx] = '\0';
    }
  }
  return result;
}