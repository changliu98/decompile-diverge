int func0(char *strr) {
  int summ = 0;
  for (int i = 0; strr[i] != '\0'; i++) {
    summ += (strr[i] - 'a' + 1);
  }
  if (summ % 26 == 0) {
    return 'z';
  } else {
    summ = summ % 26;
    return ('a' + summ - 1);
  }
}