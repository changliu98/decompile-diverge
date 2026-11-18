int func0(int a, int b) {
    int sum = 0;
    int i = 1;
    int limit = (a < b) ? a : b;

    while (i < limit) {
        if (a % i == 0 && b % i == 0) {
            sum += i;
        }
        i++;
    }
    
    return sum;
}