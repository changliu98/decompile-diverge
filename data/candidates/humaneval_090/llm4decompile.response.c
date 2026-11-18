int func0(int *lst, int size)
{
    if (size < 2)
        return -1;
    int first = 0x7fffffff;
    int second = 0x7fffffff;
    for (int i = 0; i < size; i++) {
        if (lst[i] < first) {
            second = first;
            first = lst[i];
        } else if (lst[i] < second && lst[i] != first) {
            second = lst[i];
        }
    }
    if (second == 0x7fffffff)
        return -1;
    return second;
}