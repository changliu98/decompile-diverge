void gsdate(int day, int month, int year, int *out) {
    year += 100;
    
    if (month > 2) {
        month -= 3;
    } else {
        month += 9;
        year -= 1;
    }
    
    year *= 1461;
    year /= 4;
    
    month *= 153;
    month += 2;
    month /= 5;
    
    int result = day + month + year;
    result -= 36466;
    
    if (result > 59) {
        result -= 1;
    }
    
    *out = result;
}