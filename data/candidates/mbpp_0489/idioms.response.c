int func0(int n, int a[])
{
    int min = a[0];
    int count = 1;
    int i = 1;
    while (i < n) {
        if (a[i] > min) {
            min = a[i];
            count = 1;
        } else if (a[i] == min) {
            count++;
        }
        i++;
    }
    return count;
}