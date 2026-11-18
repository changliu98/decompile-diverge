char* func0(const char* N) {
  int l = strlen(N);
  if (N[l - 1] == '0' || N[l - 1] == '2' ||
      N[l - 1] == '4' || N[l - 1] == '6' ||
      N[l - 1] == '8' || N[l - 1] == 'A' ||
      N[l - 1] == 'C' || N[l - 1] == 'E') {
    return "Even";
  } else {
    return "Odd";
  }
}