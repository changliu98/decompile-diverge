char* func0(int a, int b) {
    char* result;
    if (a > b) {
        result = "";
    } else {
        int sum = a + b;
        int quotient = sum / 2;
        char* buffer = (char*)malloc(33);
        buffer[0] = '\0';
        int index = 32;
        buffer[index] = '\0';
        
        while (quotient > 0) {
            buffer[--index] = (quotient % 2) + '0';
            quotient /= 2;
        }
        result = &buffer[index];
    }
    return result;
}