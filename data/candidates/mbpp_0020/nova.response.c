int func0(long long int n) {
    int flag = 0;
    if (n % 2 == 0)
        flag = 0;
    else {
        long long int i = 0;
        while (1) {
            if (n % 2 == 0) {
                n = n / 2;
                i++;
                if (i == n) {
                    flag = 1;
                    break;
                }
            } else {
                flag = 0;
                break;
            }
        }
    }
    if (flag % 2 == 0)
        return 0;
    else
        return 1;
}