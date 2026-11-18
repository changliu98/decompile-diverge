void get_month_and_day_by_row(int row, int year, int *month, int *day) {
  int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  *day = 0;
  *month = 0;
  int sum = 0;
  int is_leap_year = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  if (row > 0 && row <= (365 + is_leap_year)) {
    if (is_leap_year) {
      month_days[1]++;
    }
    while (row > sum) {
      sum += month_days[(*month)++];
    }
    *day = row - sum + month_days[*month - 1];
  }
}