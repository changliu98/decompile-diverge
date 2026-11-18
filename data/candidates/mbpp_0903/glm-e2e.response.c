int func0(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int temp = i;
        while (temp != 0) {
            if (temp % 2 == 0) {
                count++;
            }
            temp = temp / 2;
        }
    }
    return count;
}