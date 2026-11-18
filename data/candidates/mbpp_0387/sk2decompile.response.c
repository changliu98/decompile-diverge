char* func0(char* str) {
  int len = strlen(str);
  if (str[len - 1] == '0' || str[len - 1] == '2' || str[len - 1] == '4' ||
      str[len - 1] == '6' || str[len - 1] == '8' || str[len - 1] == 'A' ||
      str[len - 1] == 'C' || str[len - 1] == 'E') {
    return "Even";
  } else {
    return "Odd";
  }
}