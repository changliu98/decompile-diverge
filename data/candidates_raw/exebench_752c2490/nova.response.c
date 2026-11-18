int func0(int *a, int n) {
    int i = 0;
    int flag;
    while (i < n - 2) {
        if (a[i] > 0) {
            a[i + 2] -= 3 * a[i];
            a[i + 1] -= 2 * a[i];
            a[i] = 0;
        } else if (a[i] < 0) {
            flag = 0;
            break;
        } else {
            if (a[n - 1] == 0) {
                if (a[n - 2]!= 0)
                    flag = 0;
                else
                    flag = 1;
            } else
                flag = 1;
            break;
        }
        i++;
    }
    return flag;
}