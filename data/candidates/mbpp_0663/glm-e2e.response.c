int func0(int param1, int param2, int param3) {
    int max_val = -2147483648; // 0x80000000
    int i = 0;

    while (i <= param1) {
        if (i % param2 == param3) {
            if (max_val < i) {
                max_val = i;
            }
        }
        i++;
    }

    if (max_val >= 0 && max_val <= param1) {
        return max_val;
    } else {
        return -1;
    }
}