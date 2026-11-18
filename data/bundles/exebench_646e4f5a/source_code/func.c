#include <stdio.h>

void squeeze_alt(char *str1, char *str2) {
 int i, j, k;
 int found;

 for (i = j = 0; str1[i] != '\0'; i++) {
  found = 0;
  for (k = 0; str2[k] != '\0' && found != 1; k++) {
   if (str1[i] == str2[k]) {
    found = 1;
   }
  }
  if (found == 0)
   str1[j++] = str1[i];
 }
 str1[j] = '\0';
}
