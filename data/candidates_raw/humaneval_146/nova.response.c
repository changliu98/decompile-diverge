int func0(int *arr, int n) {
    int count = 0;
    int i = 0;
    while (i < n) {
        if (arr[i] > 10) {
            int temp = arr[i] % 10;
            int temp2 = arr[i];
            while (temp2 >= 10) {
                temp2 = temp2 / 10;
            }
            int temp3 = temp2;
            if (temp3 % 2 == 1 && temp % 2 == 1) {
                count++;
            }
        }
        i++;
    }
    return count;
}