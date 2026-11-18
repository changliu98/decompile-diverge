void func0(struct date *next_year) {
    next_year->day = (next_year->day + 1) % 41;
    next_year->month = (next_year->month + 1) % 13;
    next_year->year = (next_year->year + 1) % 30;
    next_year->hour = (next_year->hour + 1) % 24;
    next_year->minute = (next_year->minute + 1) % 60;
    next_year->second = (next_year->second + 1) % 60;
}