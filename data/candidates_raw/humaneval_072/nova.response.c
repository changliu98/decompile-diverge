int func0(int *arr, int n, int sum) {
    int i = 0, j = 0, s = 0, flag;
    while (1) {
        if (j < n / 2) {
            if (arr[i]!= arr[n - 1 - i]) {
                flag = 0;
                break;
            }
            s += arr[i] + arr[n - 1 - i];
            i++;
            j++;
        } else {
            if (n % 2 == 1) {
                s += arr[n / 2];
            }
            flag = (s <= sum)? 1 : 0;
            break;
        }
    }
    return flag % 2;
}