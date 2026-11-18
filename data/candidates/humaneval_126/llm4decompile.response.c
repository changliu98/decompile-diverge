int func0(int *lst, int lst_size) {
    int i;
    for (i = 0; i < lst_size; i++) {
        if (i > 0 && lst[i] < lst[i - 1]) {
            return 0;
        }
        if (i > 1 && lst[i] == lst[i - 1] && lst[i] == lst[i - 2]) {
            return 0;
        }
    }
    return 1;
}