int summe(int *a, int *b) {
    char result = 1;
    
    if (*a != 0) {
        *b += *a;
        *a -= 1;
        result = summe(a, b) != 0;
    }
    
    return result & 1;
}