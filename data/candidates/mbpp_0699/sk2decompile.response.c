int _hamming_distance(char *s1, char *s2) {
  int i, len, distance = 0;
  len = strlen(s1);
  for (i = 0; i < len; i++) {
    if (s1[i] != s2[i]) {
      distance++;
    }
  }
  if (distance % 2 == 0) {
    return distance / 2;
  } else {
    return -1;
  }
}