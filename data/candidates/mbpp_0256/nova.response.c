int func0(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int flag;
        if (i < 2) {
            continue;
        }
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                flag = 0;
                break;
            } else {
                flag = 1;
            }
        }
        if (flag) {
            count++;
        }
    }
    return count;
}