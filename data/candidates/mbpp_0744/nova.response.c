int func0(int *arr, int n) {
    int i = 0;
    bool flag;
    while (i < n) {
        if (arr[i] == 0) {
            flag = true;
            break;
        } else
            flag = false;
        i++;
    }
    return flag;
}