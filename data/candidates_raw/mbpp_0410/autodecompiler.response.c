int get_min_int(char **str, int n) {
  int i;
  int val;
  int min = 0x7fffffff;

  for (i = 0; ; i++) {
    if (i < n) {
      if (___isoc99_sscanf(str[i], "%d", &val)) {
        if (val < min)
          min = val;
      }
    } else {
      break;
    }
  }

  return min;
}