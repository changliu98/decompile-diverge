int func0(int arr[], int n)
{
    int jumps[200];
    int i, j;
    if (n == 0 || arr[0] == 0)
        return 0x7fffffff;
    jumps[0] = 0;
    for (i = 1; i < n; i++) {
        jumps[i] = 0x7fffffff;
        for (j = 0; j < i; j++) {
            if (arr[j] + j >= i && jumps[j] != 0x7fffffff) {
                jumps[i] = ((jumps[i]) < (jumps[j] + 1) ? (jumps[i]) : (jumps[j] + 1));
                break;
            }
        }
    }
    return jumps[n - 1];
}