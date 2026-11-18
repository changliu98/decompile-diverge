void easterj(int year, int *month, int *day) {
    int a = year % 4;
    int b = year % 7;
    int c = year % 19;
    int d = (13 * c + 15) % 30;
    int e = (2 * a + 4 * b - d + 34) % 7;
    
    *month = (d + e + 114) / 31;
    *day = (d + e + 114) % 31 + 1;
}