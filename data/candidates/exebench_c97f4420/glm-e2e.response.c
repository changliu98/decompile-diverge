void get_month_and_day_by_row(int row, int year, int *month, int *day) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    *month = 0;
    *day = 0;
    int total_days = 0;
    
    // Determine if the given year is a leap year
    int is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    
    // If the row is out of bounds, return (leaving month and day as 0)
    if (row <= 0 || row > 365 + is_leap_year) {
        return;
    }
    
    // Adjust February's days if it's a leap year
    if (is_leap_year) {
        days_in_month[1]++;
    }
    
    // Find the month
    while (row > total_days) {
        (*month)++;
        total_days += days_in_month[*month - 1];
    }
    
    // Calculate the exact day of the month
    *day = row - total_days + days_in_month[*month - 1];
}