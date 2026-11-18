void func0(int *lst, int size, int *out)
{
    int i;
    int j;
    int index = 0;
    int l;
    int r;
    int temp;

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (lst[j] < lst[i]) {
                temp = lst[i];
                lst[i] = lst[j];
                lst[j] = temp;
            }
        }
    }

    l = 0;
    r = size - 1;

    while (l <= r) {
        if (l == r) {
            out[index] = lst[l];
            index++;
        } else {
            out[index] = lst[l];
            index++;
            out[index] = lst[r];
            index++;
            l++;
            r--;
        }
    }
}