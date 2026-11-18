bool validateRegexSyntax(const char *regex) {
  unsigned int i;
  char c;
  int open_parentheses = 0;
  bool in_character_class = false;
  bool escaped = false;
  bool in_character_class_literal = false;
  bool in_character_class_range = false;
  bool valid_before = false;
  bool valid_after_pipe = false;
  bool valid_after_quantifier = false;
  for (i = 0; regex[i] != '\0'; i++) {
    c = regex[i];
    if (escaped) {
      escaped = false;
      valid_before = true;
      valid_after_pipe = false;
      valid_after_quantifier = false;
      continue;
    }
    if (c == '\\') {
      escaped = true;
      continue;
    }
    if (in_character_class) {
      if (c == ']') {
        if (!in_character_class_literal) {
          return false;
        }
        in_character_class = false;
        valid_before = true;
        valid_after_pipe = false;
        valid_after_quantifier = false;
        continue;
      }
      in_character_class_literal = true;
      continue;
    }
    if (c == '[') {
      in_character_class = true;
      in_character_class_literal = false;
      continue;
    }
    if (c == ']') {
      return false;
    }
    if (c == '(') {
      open_parentheses++;
      valid_before = false;
      valid_after_pipe = false;
      valid_after_quantifier = false;
      continue;
    }
    if (c == ')') {
      if (open_parentheses == 0 || !valid_before) {
        return false;
      }
      open_parentheses--;
      valid_before = true;
      valid_after_pipe = false;
      valid_after_quantifier = false;
      continue;
    }
    if (c == '|') {
      if (!valid_before) {
        return false;
      }
      valid_before = false;
      valid_after_pipe = true;
      valid_after_quantifier = false;
      continue;
    }
    if (c == '*' || c == '+' || c == '?') {
      if (!valid_before || valid_after_quantifier) {
        return false;
      }
      valid_after_pipe = false;
      valid_after_quantifier = true;
      continue;
    }
    valid_before = true;
    valid_after_pipe = false;
    valid_after_quantifier = false;
  }
  if (escaped || in_character_class || open_parentheses || valid_after_pipe) {
    return false;
  }
  return true;
}