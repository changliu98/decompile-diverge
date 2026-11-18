int func0(int a, int b) {
    int count = 0;
    for (int i = a; i <= b; i++) {
        if (i >= 10 && i <= 15) {
            count++;
        } else if (i > 15) {
            int temp = i;
            while (temp != 0) {
                if (temp % 16 >= 10) {
                    count++;
                }
                temp /= 16;
            }
        }
    }
    return count;
}