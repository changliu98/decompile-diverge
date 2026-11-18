















static void get_month_and_day_by_row(const int row, const int year, int *const month, int *const day) {
 int monthdays;
 int is_leap;
 int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


 *day = 0;
 *month = 0;
 monthdays = 0;

 is_leap = (((year) % 4 == 0 && (year) % 100 != 0) || (year) % 400 == 0);


 if ( (row <= 0) || (row > 365 + is_leap) ) {
  return;
 }


 if ( is_leap ) {
  ++days_in_month[1];
 }


 while ( row > monthdays ) {
  monthdays += days_in_month[(*month)++];
 }
    *day = row - monthdays + days_in_month[*month-1];
}
