void get_month_and_day_by_row(int row,int year,int *month,int *day)

{
  int iVar1;
  bool local_59;
  int days_in_month [12];
  int is_leap;
  int monthdays;
  int *day_local;
  int *month_local;
  int year_local;
  int row_local;
  
  memcpy(days_in_month,&DAT_00102030,0x30);
  *day = 0;
  *month = 0;
  monthdays = 0;
  if ((year % 4 != 0) || (local_59 = true, year % 100 == 0)) {
    local_59 = year % 400 == 0;
  }
  if ((0 < row) && (row <= (int)(local_59 + 0x16d))) {
    if (local_59 != 0) {
      days_in_month[1] = days_in_month[1] + 1;
    }
    for (; monthdays < row; monthdays = days_in_month[iVar1] + monthdays) {
      iVar1 = *month;
      *month = iVar1 + 1;
    }
    *day = (row - monthdays) + days_in_month[*month + -1];
  }
  return;
}