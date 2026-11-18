void get_month_and_day_by_row(int day, int year, int *month, int *day_in_month)
{
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int is_leap;
  int monthdays = 0;
  int *monthp = month;
  int *dayp = day_in_month;
  *dayp = 0;
  *monthp = 0;
  monthdays = 0;
  is_leap = (year % 4 == 0);
  is_leap = (is_leap && (year % 100 != 0)) ? 1 : 0;
  is_leap = (is_leap && (year % 400 == 0)) ? 1 : 0;
  if (day > 0 && day <= (is_leap + 365)) {
    if (is_leap)
      days_in_month[1]++;
    while (day > monthdays) {
      monthdays += days_in_month[(*monthp)++];
    }
    monthdays -= days_in_month[*monthp - 1];
    *dayp = day - monthdays;
  }
}