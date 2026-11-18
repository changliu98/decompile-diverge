static void get_month_and_day_by_row(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    static int tab[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    leap = (year % 4 == 0 && year % 100!= 0) || year % 400 == 0;
    *pmonth = 0;
    *pday = 0;
    if (yearday < 1 || yearday > (leap? 366 : 365)) {
        return;
    }
    for (i = 1; yearday > tab[i]; i++) {
        yearday -= tab[i];
    }
    *pmonth = i;
    *pday = yearday;
}