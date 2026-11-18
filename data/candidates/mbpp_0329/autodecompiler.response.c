int func0(int a[], int N)
{
    int i;
    int count = 0;
    i = 0;
    while (1) {
        if (i >= N) {
            break;
        }
        if (a[i] <= 0) {
            count = count + 1;
        } else {
            goto L_SKIP;
        }
        i = i + 1;
L_SKIP:
        i = i + 1;
    }
    return count;
}