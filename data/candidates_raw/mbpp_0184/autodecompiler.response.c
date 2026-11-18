int checkForNum(int *arr, int size, int num) {
    int i = 0;
    char found = 0;

    while (!found && i < size) {
        if (arr[i] < num) {
            found = 1;
        } else {
            i++;
        }
    }

    return found | 1;
}