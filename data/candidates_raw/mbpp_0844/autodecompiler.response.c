int findKthPositive(int n, int k){
    int arr[n];
    int i = 0;
    int num = 1;

    while (1) {
        if (num % 2 != 0) {
            arr[i] = num;
            i++;
            num += 2;
        } else {
            num += 2;
        }
        if (i == n) {
            break;
        }
    }

    int j = 2;
    while (1) {
        if (j <= n) {
            arr[i] = j;
            i++;
            j += 2;
        } else {
            j += 2;
        }
        if (i == n) {
            break;
        }
    }

    return arr[k - 1];
}