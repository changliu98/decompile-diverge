int meat_time_which_month(unsigned char *month, unsigned int len) {
  int i = 0;
  char found = 0;
  if (len == 3) {
    while (!found && i < 12) {
      if (month[0] == months[i][0] && month[1] == months[i][1] &&
          month[2] == months[i][2]) {
        found = 1;
      } else {
        i++;
      }
    }
  }
  if (!found) {
    return -1;
  }
  return i;
}