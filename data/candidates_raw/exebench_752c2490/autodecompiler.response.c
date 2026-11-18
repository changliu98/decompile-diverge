int check_last_borrow(int *num, int length) {
    int i = 0;
    while (1) {
        if (i < length - 2) {
            if (num[i] > 0) {
                num[i + 2] -= 3 * num[i];
                num[i + 1] -= 2 * num[i];
                num[i] = 0;
            } else if (num[i] < 0) {
                break;
            }
        } else {
            char flag = ((num[length - 1] == 0) && (num[length - 2] == 0)) ? 1 : 0;
            i = (flag == 1) ? 1 : 0;
            break;
        }
        i++;
    }
    return i;
}