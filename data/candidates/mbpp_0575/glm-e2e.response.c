int func0(int a, int b, int c, int d) {
    int count = 0;
    int i = c;
    
    while (i <= d) {
        if (i % a == 0) {
            count++;
        }
        if (count == b) {
            break;
        }
        i++;
    }
    
    return i;
}