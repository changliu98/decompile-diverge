void eastero(int year, int *month, int *day) {
    int a = year % 19;
    int b = (a * 19 + 15) % 30;
    int c = (year + year / 4 + b) % 7;
    int d = 10;
    
    if (year > 1600) {
        int e = year / 100 - 16;
        d += e - e / 4;
    }
    
    int e = b - c + d;
    
    *month = e / 30 + 3;
    *day = (e + 27 + (e + 6) / 40) % 31 + 1;
}