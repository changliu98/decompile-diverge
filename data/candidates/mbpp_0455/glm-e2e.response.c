bool func0(int month) {
    bool is_long_month;
    
    if (month == 1 || month == 3 || month == 5 || month == 7 || 
        month == 8 || month == 10 || month == 12) {
        is_long_month = true;
    } else {
        is_long_month = false;
    }
    
    return is_long_month;
}