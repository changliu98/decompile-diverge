void set_stimulus(unsigned char *stimulus, char *str) {
  while (*str) {
    if (*str >= '0' && *str <= '7') {
      *stimulus &= ~(1 << (*str - '0'));
    }
    str++;
  }
}