bool _isRotation(char *s1, char *s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  char *s2_rotated = malloc(2 * len2 + 1);
  int i;
  for (i = 0; i < len2; i++) {
    strncpy(s2_rotated, s2 + i, len2 - i);
    strncpy(s2_rotated + len2 - i, s2, i);
    s2_rotated[len2] = '\0';
    if (strstr(s1, s2_rotated)) {
      free(s2_rotated);
      return true;
    }
  }
  free(s2_rotated);
  return false;
}