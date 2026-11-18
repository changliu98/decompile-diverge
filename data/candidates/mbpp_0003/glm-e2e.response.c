int func0(int n) {
    int flag = 0;
    int i = 2;
    while (i <= (int)sqrt((double)n)) {
        if (n % i == 0) {
            flag = 1;
        }
        i++;
    }
    return flag;
}