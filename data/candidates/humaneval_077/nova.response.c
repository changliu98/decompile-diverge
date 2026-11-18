int func0(int n) {
    int i = 0, flag;
    while (1) {
        if (i * i * i <= abs(n)) {
            if (i * i * i == abs(n)) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            break;
        }
        i++;
    }
    return flag;
}