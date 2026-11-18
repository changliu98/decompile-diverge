void get_month_and_day_by_row(int row, int year, int *month, int *day)
{
 int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 int is_leap;
 int monthdays;

 *day = 0;
 *month = 0;
 monthdays = 0;

 is_leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

 if (row > 0 && row <= 365 + is_leap) {
  if (is_leap) {
   days_in_month[1]++;
  }

  while (monthdays < row) {
   monthdays += days_in_month[*month];
   *month += 1;
  }

  *day = days_in_month[*month - 1] + (row - monthdays);
 }
}