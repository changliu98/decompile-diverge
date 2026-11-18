

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <ctype.h>

#include <stdbool.h>



bool func0(const char *p) {
  int len = strlen(p);
  bool hasLower = false;
  bool hasUpper = false;
  bool hasDigit = false;
  bool hasSpecial = false;
  if (len < 6 || len > 12) {
    return false;
  }
  for (int i = 0; i < len; i++) {
    if (islower(p[i])) {
      hasLower = true;
    } else if (isupper(p[i])) {
      hasUpper = true;
    } else if (isdigit(p[i])) {
      hasDigit = true;
    } else if (p[i] == '$' || p[i] == '#' || p[i] == '@') {
      hasSpecial = true;
    } else if (isspace(p[i])) {
      return false;
    }
  }
  return hasLower && hasUpper && hasDigit && hasSpecial;
}
