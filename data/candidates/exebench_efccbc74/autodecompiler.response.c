int meat_time_which_month(char *month, size_t len) {
  int i_month = 0;
  char b_found = 0;

  if (len == 3) {
    while (1) {
      char b_continue = !b_found;
      if (!b_continue) { b_continue = i_month < 12; }
      if (!b_continue) { break; }

      if (month[0] == meat_time_which_month_a_ref_month[i_month * 3 + 0]) {
        if (month[1] == meat_time_which_month_a_ref_month[i_month * 3 + 1]) {
          if (month[2] == meat_time_which_month_a_ref_month[i_month * 3 + 2]) {
            b_found = 1;
            continue;
          }
        }
      }

      i_month++;
    }
  } else {

  }

  if (!b_found) { i_month = -1; }

  return i_month;
}