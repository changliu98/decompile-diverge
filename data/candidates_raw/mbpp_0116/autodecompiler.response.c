int from_digits(int digits[], int num_digits) {
    int i;
    int ret = 0;

    for (i = 0; ; i++) {
 if (i >= num_digits) break;
 ret = ret * 10 + digits[i];
    }

    return ret;
}