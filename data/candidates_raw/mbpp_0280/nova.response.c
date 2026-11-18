int func0(int *arr, int n, int x, int *i) {
    *i = 0;
    bool found = false;
    while (!found) {
        if (*i < n) {
            if (arr[*i] == x) {
                found = true;
            } else {
                *i = *i + 1;
            }
        } else {
            break;
        }
    }
    return!found;
}