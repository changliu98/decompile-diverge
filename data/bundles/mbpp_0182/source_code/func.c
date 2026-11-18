

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <ctype.h>



void func0(char *string, char uppercase_characters[],
           char lowercase_characters[], char numerical_characters[],
           char special_characters[]) {
  int upper_idx = 0, lower_idx = 0, num_idx = 0, special_idx = 0;
  int len = strlen(string);
  for (int i = 0; i < len; i++) {
    if (isupper(string[i])) {
      uppercase_characters[upper_idx++] = string[i];
    } else if (islower(string[i])) {
      lowercase_characters[lower_idx++] = string[i];
    } else if (isdigit(string[i])) {
      numerical_characters[num_idx++] = string[i];
    } else if (string[i] == ',' || string[i] == '.' || string[i] == '!' ||
               string[i] == '?') {
      special_characters[special_idx++] = string[i];
    }
  }
  uppercase_characters[upper_idx] = '\0';
  lowercase_characters[lower_idx] = '\0';
  numerical_characters[num_idx] = '\0';
  special_characters[special_idx] = '\0';
}
